# las2pcd

Photogrammetry and Geomatics Group, ICube UMR 7357 INSA Strasbourg

Simple function written in C++ used to convert .LAS point cloud to PCL-compatible .PCD format.

Required dependencies:
- PCL (http://pointclouds.org/)
- libLAS (https://www.liblas.org/)

Ubuntu installation:
	
	apt-get install -y git cmake
	
	apt-get install -y libpcl-dev liblas-dev liblas-c-dev
	
	git clone -b ubuntu-singularity https://github.com/jimmy4345/las2pcd.git
	
	cd las2pcd
	
	cmake .
	
	make
	
How to use:

    ./las2pcd /your/lasfile/directory /store/pcd/directory



