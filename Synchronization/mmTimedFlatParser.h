#ifndef __mmTimedFlatParser__
#define __mmTimedFlatParser__

#include "mmTrack.h"

namespace MoMa {

    class TimedFlatParser {

      public:

		TimedFlatParser( std::string const &fileName, Track *track );
        void load( std::string const &fileName, Track *track );
		arma::vec timestamps;
    };
}

#endif
