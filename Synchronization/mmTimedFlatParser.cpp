#include "mmTimedFlatParser.h"

using namespace std;
using namespace MoMa;

TimedFlatParser::TimedFlatParser( std::string const &fileName, MoMa::Track *track ) {

    load( fileName, track );
}

void TimedFlatParser::load( string const &fileName, Track *track ) {

    ifstream datFile( fileName.c_str() ); // Open file

    if( !datFile.is_open() ) {

        std::cout << "Track: File could not be opened!" << endl;
        return; // We alert on stdout and quit if no file!
    }

    track->clearData();

    unsigned int nbFrames = 0, nbNodes = 0;
    while ( datFile.good() ) {

        string curLine;
        stringstream curStrm;
        vector<string> rawData;

        getline( datFile, curLine );

        if( curLine != "" && curLine != " " && curLine != "\t" && curLine != "\n" ) {

            curStrm.clear();
            curStrm << curLine;
            if ( nbFrames == 0 ) {

				if (curLine[curLine.size() - 1] == ' ')
					nbNodes = (std::count(curLine.begin(), curLine.end(), ' ')) / 3;
				else nbNodes = (std::count(curLine.begin(), curLine.end(), ' ') + 1) / 3;
            }
            nbFrames++;
        }
    }

    datFile.clear() ;
    datFile.seekg(0, ios::beg) ;

	timestamps = arma::vec( nbFrames );
    
    arma::cube positionData( 3, nbNodes, nbFrames );
    unsigned int cptFrames = 0;
    while ( datFile.good() ) {

        string curLine;
        stringstream curStrm;
        vector<string> rawData;

        getline( datFile, curLine );

        if( curLine != "" && curLine != " " && curLine != "\t" && curLine != "\n" ) {

            Frame oneFrame;

            curStrm.clear();
            curStrm << curLine;
            unsigned int cptNodes = 0;

			string ts;
			curStrm >> ts;
			timestamps[cptFrames] = atof( ts.c_str() )/1000;
			if ( cptFrames > 0 ) timestamps[cptFrames] -= timestamps[0];
            while( curStrm.good() ) {

                string value[3];

                curStrm >> value[0];
                curStrm >> value[1];
                curStrm >> value[2];

                if( ( value[0] == "NaN" && value[1] == "NaN" && value[2] == "NaN" ) ||
                    ( atof(value[0].c_str()) > MOMAINF && atof( value[0].c_str() ) >
                    MOMAINF && atof( value[0].c_str()) > MOMAINF ) ) {

                        // Data are ignored and the oneNode stays with ARMA NaNs

                } else {

                    positionData( X, cptNodes, cptFrames ) = atof( value[0].c_str() );
                    positionData( Y, cptNodes, cptFrames ) = atof( value[1].c_str() );
                    positionData( Z, cptNodes, cptFrames ) = atof( value[2].c_str() );
                    cptNodes++;

                }
                if( cptNodes >= nbNodes )
                    break;
            }
            cptFrames++;
        }
    }
	timestamps[0] = 0;
    //track->setFrameRate( 30 );
   // std::cout << "Note: default framerate for a flat file is set at 30 fps. Do not forget to set the right framerate in your track." << endl;
    track->position.setData( timestamps, positionData );
    datFile.close();
}
