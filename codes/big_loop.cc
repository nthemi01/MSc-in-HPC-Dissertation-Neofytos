int n = _jets.size();//The number of particles left to be reconstructed
...
while (n > 0) { 
//Pointers jetA and jetB are initiated
jetA = best->jet;jetB = jetA->NN;
...
for (int itile = 0; itile < n_near_tiles; itile++) {//loop through all tiles
    Tile * tile_ptr = &_tiles[tile_union[itile]];
    // run over all jets in the current tile
    for(TiledJet* jetI=tile_ptr->head;jetI!=NULL;jetI=jetI->next){
        // see if jetI had jetA or jetB as a NN--if so recalculate the NN
        if (jetI->NN == jetA || (jetI->NN == jetB && jetB != NULL)) {
            jetI->NN_dist = _R2;
            jetI->NN      = NULL;
            // now go over tiles that are neighbours of I (include own tile)
            for (Tile ** near_tile  = tile_ptr->begin_tiles; 
                    near_tile != tile_ptr->end_tiles; near_tile++) {
                // and then over the contents of that tile
                for (TiledJet * jetJ  = (*near_tile)->head; 
                        jetJ != NULL; jetJ = jetJ->next) {
                    double dist = _bj_dist(jetI,jetJ);
                    if (dist < jetI->NN_dist && jetJ != jetI) {
                    jetI->NN_dist = dist; jetI->NN = jetJ;
                    }
                }
            }
            diJ[jetI->diJ_posn].diJ = _bj_diJ(jetI);// update diJ kt-dist
        }
        // check whether new jetB is closer than jetI's current NN and
        // if jetI is closer than jetB's current (evolving) nearest
        // neighbour. Where relevant update things
        if (jetB != NULL) {
            double dist = _bj_dist(jetI,jetB);
            if (dist < jetI->NN_dist) {|\label{line:crit1start}|
                if (jetI != jetB) {
                    jetI->NN_dist = dist;
                    jetI->NN = jetB;
                    diJ[jetI->diJ_posn].diJ=_bj_diJ(jetI);
                    //update diJ
                }
            }|\label{line:crit1end}|
            if (jetI != jetB)
            { 
                    if (dist < jetB->NN_dist)
                    {
                        jetB->NN_dist = dist;
                        jetB->NN      = jetI;
                    }
            }
        }
    }
}
    // finally, register the updated kt distance for B. n is also altered.
    if (jetB != NULL) {diJ[jetB->diJ_posn].diJ = _bj_diJ(jetB);}
}