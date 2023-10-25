# las2pcd

Simple function written in C++ used to convert .LAS point cloud to PCL-compatible .PCD format.

Required dependencies:
- PCL (http://pointclouds.org/)
- libLAS (https://www.liblas.org/)

Ubuntu 18.04 installation:
	
	apt-get install -y git cmake
	
	apt-get install -y libpcl-dev liblas-dev liblas-c-dev
	
	git clone https://github.com/jimmy4345/las2pcd.git
	
	cd las2pcd
	
	cmake .
	
	make
	
How to use:

    ./las2pcd /your/lasfile/directory /store/pcd/directory




# las2pcd

Yen En Huang, POINT Lab, Geomatics NCKU, Taiwan

## Overview
Simple function written in C++ used to convert multiple .LAS point cloud data to PCL-compatible .PCD format.

## Required dependencies
* PCL (http://pointclouds.org/)
* ~~libLAS (https://www.liblas.org/)~~ (**Ubuntu 18.04 and older**)
* LAStools (http://lastools.org) (**Above Ubuntu 18.04**)

## How to install dependencies

Ubuntu 18.04 installation: (**No longer active**)
```cpp
// install dependencies
sudo apt-get update
sudo apt-get install -y git cmake
sudo apt-get install -y libpcl-dev liblas-dev liblas-c-dev

// build
git clone https://github.com/jimmy4345/las2pcd.git
cd las2pcd
mkdir build && cd build
cmake ..
make
```


Ubuntu 22.04 installation: (**active**)
```cpp
// install pcl dependencies
sudo apt-get update
sudo apt-get install -y git cmake
sudo apt-get install -y libpcl-dev
```

```cpp
// install LAStools dependencies
git clone https://github.com/LAStools/LAStools.git
cd LAStools
mkdir build && cd build
cmake ..
make
sudo make install
```



```cpp
// build
git clone https://github.com/jimmy4345/las2pcd.git
cd las2pcd
mkdir build && cd build
cmake ..
make
```

	
## How to use:

```
./las2pcd /your/lasfile/directory /store/pcd/directory
```
    
    
    
    






