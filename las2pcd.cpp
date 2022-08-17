#include <iostream>
#include <cstdlib>
#include <liblas/liblas.hpp>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <cstring>

using namespace std;

char *getExtension(char *fileName) 
{
	int len = strlen(fileName);
	int i = len;
	while (fileName[i] != '.' && i > 0) { i--; }

	if (fileName[i] == '.') {
		return &fileName[i + 1];
	}
	else {
		return &fileName[len];
	}
}

int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) 
	{
		//cout << string(dirp->d_name) << '\n';
		if (strcmp(getExtension(dirp->d_name),"las") == 0)
		{
			files.push_back(string(dirp->d_name));
		}
    }
    closedir(dp);
    return 0;
}

int main (int argc, char *argv[])
{
	
	cout << "===================================================================" << endl;
	cout << "LAS2PCD - Converts .las point clouds into PCL-friendly format .pcd" << endl;
	cout << "Current for Ubuntu18.04 using liblas dev package(Ubuntu 20.04 can't use, need to check)" << endl;
	cout << "===================================================================" << endl;
	cout << endl;

	// cout << "Enter full .las file path: (or you can also drag the file here)" << endl;
    
	// getline(cin, filePath);
	// Edited to make fully command-line:
	string input_dir = string(argv[1]);
	string output_dir = string(argv[2]);
    vector<string> files = vector<string>();


	getdir(input_dir,files);


	//cout << files.size() << endl;   

	for (unsigned int i = 0;i < files.size();i++){
		//cout << files.size() << endl;
		string lasfile_path;
		lasfile_path = input_dir + "/" + files[i];

		std::cerr << "INFO : Loading : " << lasfile_path << std::endl;


		// instancing a new PCL(XYZI) pointcloud object
    	pcl::PointCloud<pcl::PointXYZI> *cloud1 = new pcl::PointCloud<pcl::PointXYZI>;

		// Opening  the las file
    	std::ifstream ifs(lasfile_path.c_str(), std::ios::in | std::ios::binary);

		// Safeguard against opening failure
		if(ifs.fail()){
        	std::cerr << "ERROR : Impossible to open the file : " << lasfile_path <<std::endl;
        	return 1;
    	}

		liblas::ReaderFactory f;
    	liblas::Reader reader = f.CreateWithStream(ifs); // reading las file
    	unsigned long int nbPoints=reader.GetHeader().GetPointRecordsCount();

		// Fill in the cloud data
		cloud1->width    = nbPoints;				// This means that the point cloud is "unorganized"
		cloud1->height   = 1;						// (i.e. not a depth map)
		cloud1->is_dense = false;
		cloud1->points.resize (cloud1->width * cloud1->height);

		cout << "INFO : " << cloud1->points.size () << " points detected in " << lasfile_path << endl;

		int j = 0;				// counter
		/*uint16_t r1, g1, b1;	// RGB variables for .las (16-bit coded)
		int r2, g2, b2;			// RGB variables for converted values (see below)
		uint32_t rgb;			// "packed" RGB value for .pcd*/

		while(reader.ReadNextPoint()){
			// get XYZ information
			cloud1->points[j].x = (reader.GetPoint().GetX());
	    	cloud1->points[j].y = (reader.GetPoint().GetY());
	    	cloud1->points[j].z = (reader.GetPoint().GetZ());

			// get Intensity information
			cloud1->points[j].intensity = (reader.GetPoint().GetIntensity());


			/*		
			// get RGB information. Note: in liblas, the "Color" class can be accessed from within the "Point" class, thus the triple gets
			r1 = (reader.GetPoint().GetColor().GetRed());
			g1 = (reader.GetPoint().GetColor().GetGreen());
			b1 = (reader.GetPoint().GetColor().GetBlue()); 

			// .las stores RGB c	cout << endl;: must "pack" the RGB into one single integer and then reinterpret them as float
			rgb = ((int)r2) << 16 | ((int)g2) << 8 | ((int)b2);

			cloud.points[i].rgb = *reinterpret_cast<float*>(&rgb);*/

			j++; // ...moving on
		}


		// Allows output file to be set:
		pcl::io::savePCDFileASCII (output_dir + "/" + files[i].replace(files[i].find("las"),3,"pcd"), *cloud1);
  
		std::cerr << "Saved " << cloud1->points.size () << output_dir + "/" + files[i] << std::endl;
		cout << endl;

		delete cloud1;
	}

	return 0;
 
}
