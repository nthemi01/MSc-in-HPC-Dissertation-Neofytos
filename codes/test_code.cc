#include <iostream> // needed for io
#include <cstdio>   // needed for io
#include <sstream>  // needed for internal io
#include <iomanip>  
#include <cmath>
#include <chrono>
#include <ctime>
#include <algorithm>    // for std::min
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <istream>
#include <fstream>
#include <string>
#include <sstream>

#include "fastjet/ClusterSequence.hh"
#include <fastjet/tools/Filter.hh>
#include "fastjet/PseudoJet.hh"
#include "fastjet/JetDefinition.hh"

using namespace std;
using namespace fastjet;


//This class is neccecary for the cambridge clustering algorithm. Taken "as is" from FastJet examples.
typedef JetDefinition::DefaultRecombiner DefRecomb;
class FlavourRecombiner : public  DefRecomb {
    public:
        FlavourRecombiner(RecombinationScheme recomb_scheme = E_scheme) : 
            DefRecomb(recomb_scheme) {};
        virtual std::string description() const {
            return DefRecomb::description()+" (with user index addition)";}
        /// recombine pa and pb and put result into pab
        virtual void recombine(const PseudoJet & pa, const PseudoJet & pb, 
                PseudoJet & pab) const {
            DefRecomb::recombine(pa,pb,pab);
            // Note: see the above discussion for the fact that we consider
            // negative user indices as "0"
            pab.set_user_index(max(pa.user_index(),0) + max(pb.user_index(),0));
        }
};

//Read all the events from the input file and store them to a vector of vectors
void read_input_file(vector <vector <PseudoJet> > &all_events);

//Loop through each event, perform clustering and save the reconstructed jets to a vector of vectors
void perform_clustering(vector <vector <PseudoJet> > &all_events, vector <vector <PseudoJet> > &all_jets, JetDefinition jet_def);

//print all the reconstreucted jets
void print_all(vector <vector <PseudoJet> > &all_tagged_jets);

int main(){
    // create a jet definition: 
    // a jet algorithm with a given radius parameter R
    //Depending on the desired jet algorithm to be used (anti-kt or cambridge) the appropriate JetDefinition is being uncomented
    //----------------------------------------------------------
    double R = 1.2;
    JetDefinition jet_def(antikt_algorithm, R);//use the antikt algorithm
    //FlavourRecombiner flav_recombiner; // has to be uncomented to use tha cambridge algorithm
    //JetDefinition jet_def(cambridge_algorithm, R, &flav_recombiner); has to be uncomented to use the cambridge algorithm


    vector <vector <PseudoJet> > all_events; //All the input events will be stored here
    vector <vector <PseudoJet> > all_jets; //All the reconstructed jets will be stored here

    auto start = std::chrono::system_clock::now();//Take a note of the initial time
    cerr<<"Started reading input file\n";
    read_input_file(all_events);
    auto time_to_read = std::chrono::system_clock::now();//Take a note of the time after the events have been read
    long mysize=all_events.size();//Meassure how many events were read
    std::chrono::duration<double>  diff = time_to_read-start;
    cerr<<"Read "<<mysize<<" events\nReading data took:\t"<<diff.count()<<"s\n";

    //Perform the actual clustering
    perform_clustering(all_events,all_jets,jet_def);
    auto time_to_work = std::chrono::system_clock::now();
    diff = time_to_work-time_to_read;
    std::cerr << "Analysis took:\t" << diff.count() << "s\n";

    //Print the results
    print_all(all_jets);
    auto time_to_print = std::chrono::system_clock::now();
    diff = time_to_print-time_to_work;
    std::cerr << "Printing took:\t" << diff.count() << "s\n";
}


void read_input_file(vector <vector <PseudoJet> > &all_events)
{
    vector <PseudoJet> current_event;
    string line="";
    while (getline(cin,line)) {
        if (line.substr(0,1) == "#")//In the input file, "#" means no more particles in that event
        {
            //Since all the particles of this event are saved to the vector, it is time to push-back it to the vector of vectors, and clear it to be ready for the next event
            all_events.push_back(current_event);
            current_event.clear();
        }
        else if (line.substr(0,1) == "!")//In the input file, "!" means no more events
        {
            //All the events have been read
            return;
        }
        else
        {
            //The line contains a new particle. Read the four-momentum values and add them to the vector
            istringstream linestream(line);
            double px,py,pz,E;
            linestream >> px >> py >> pz >> E;
            current_event.push_back(PseudoJet(px,py,pz,E));
        }
    }//end of the "while" loop
}//end of the function


void perform_clustering(vector <vector <PseudoJet> > &all_events, vector <vector <PseudoJet> > &all_jets,JetDefinition jet_def)
{
    for(int k=0;k<all_events.size();k++) //loop trough all the events
    {
        vector <PseudoJet> current_event = all_events[k];
        //for each event run the jet clustering 
        //with the appropriate jet definition
        ClusterSequence clust_seq(current_event, jet_def);

        //Sort the particles in the jet from larger to smaller momentum.
        //ptmin is the threashold  momentum of particles to filter out of the jet.
        double ptmin = 0; 
        vector<PseudoJet> jets = sorted_by_pt(clust_seq.inclusive_jets(ptmin));
        //save the newly reconstructed and sorted jet to the vector of vectors
        all_jets.push_back(jets);
    }//end of the loop through all events
}


void print_all(vector <vector <PseudoJet> > &all_jets)
{
    cout<<"# anti-kt jets: px, py, pz, e\n";
    for(int k=0;k<all_jets.size();k++)//iterate through all events
    {
        vector<PseudoJet> current_jet= all_jets[k];

        for(int i=0;i<current_jet.size();i++)//and all jets per event
        {
            cout<<current_jet[i].px()<<"\t"<<current_jet[i].py()<<"\t"<<current_jet[i].pz()<<"\t"<<current_jet[i].e()<<endl;
        }
        cout<<"\n\n#END\n";
    }//end of the loop through all events
}//end of the function