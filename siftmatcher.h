//
//  siftmatcher.h
//  vlfeat-bow-with-reranking
//
//  Created by willard on 8/24/15.
//  Copyright (c) 2015 wilard. All rights reserved.
//

#ifndef __vlfeat_bow_with_reranking__siftmatcher__
#define __vlfeat_bow_with_reranking__siftmatcher__

#include <stdio.h>

#ifndef SIFT_MATCHER_H
#define SIFT_MATCHER_H

#include "globals.h"

#include "Image.h"
#include<string>
#include<iostream>

extern "C" {
#include "vl/generic.h"
#include "vl/sift.h"
#include "vl/kdtree.h"
}

class siftmatcher{
public:
    siftmatcher();
    ~siftmatcher();
    
    void processTestImage( string imageName );
    void processTestImage( unsigned char* data );
    
    //Build the kdforest and add the data into the forest
    void buildForest(const double** descrArray, const int* descrSizes);
    
    //Finds all the descriptor matches between the test image and each of the library images
    //matches is the output
    void findMatches(int* matches);
    
    /////INTERNAL USE ONLY/////
    void uploadAllDescriptors(const double** descrArray, const int* descrSizes);
    void localizeDescriptor( float* ResultDescript, const double* descr, int size );
    void normalize( float* descr, int numDescr );
    void convertToGrayscale(Image img, vl_sift_pix *gray );
    int sift( float* d, float* pixels, Image I );
    void outputLibraryDescriptorsHeader( string* testNames);
    void outputSingleDescriptor( ofstream &myfile, float* Descript, string Filename, int size );
    vl_sift_pix* initializeImage( string name, Image& image );
    vl_sift_pix* initializeImage( unsigned char* data, Image& image );
    
private:
    string inputFileNames[NUMTESTS];
    float* testDescriptors;
    float* libraryDescriptors;
    int matchDelimeter[NUMTESTS+1];
    int numLibraryDescriptors;
    int numTestDescriptors;
    _VlKDForest* forest;
};


#endif

#endif /* defined(__vlfeat_bow_with_reranking__siftmatcher__) */
