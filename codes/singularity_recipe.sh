BootStrap: debootstrap #indicate that the underlying system is debian
OSVersion: trusty #specify the version
MirrorURL: http://us.archive.ubuntu.com/ubuntu/

#before reaching this point, the base OS has been installed in the image

%post #post contains commands that will be executed within the container after the base OS has been installed. 
    sed -i 's/$/ universe/' /etc/apt/sources.list #a tweak in order to grand singularity access to the list of applications that will be installed. 
    apt-get update
    
    #install gperf tools
    apt-get install google-perftools -y
    apt-get install libgoogle-perftools-dev -y

    #install the gnu compilers (not necessary. Included so that the test code can be compiled with gperf compiler flags)
    apt-get install gcc -y
    apt-get install g++ -y
    apt install build-essential -y