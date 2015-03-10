#include <cstdio>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

class VideoCodec {
    public:
    	// motion estimation (ME) on 8x8 blocks
        static const int blocksize = 8;

        typedef unsigned char u8;
	// ME result: block at coordinate r/c (row/column) has best match 
	// at bestr/bestc with a certain cost
        typedef struct {
            int r, c, bestr, bestc;
            unsigned int cost;
        } me_result_t;

        typedef std::vector<me_result_t> me_results_t;

        // PAL default, search range 16 for each block
        VideoCodec(int w = 720, int h = 576, int s = 16) : width(w), height(h), search(s) {
            frame = new u8[width * height];
            load_frame(frame, "frame0.y");
            frame_ref = new u8[width * height];    
            load_frame(frame_ref, "frame1.y");            
        }

        ~VideoCodec() {
            delete [] frame;
            delete [] frame_ref;            
        }

        std::vector<me_result_t> *motion_estimation() {
            std::vector<me_result_t> *me_results = new std::vector<me_result_t>;
            
            for (int r = 0; r < height; r += blocksize) {
                for (int c = 0; c < width; c += blocksize) {    
                    int bestr = -1, bestc = -1;
                    // perform ME for each block
                    unsigned int cost = best_estimate(r, c, bestr, bestc, search);
//                    printf("%d/%d -> %d/%d: %d\n", r, c, bestr, bestc, cost);

		    // and store result
                    me_result_t me_r = {r, c, bestr, bestc, cost}; 
                    me_results->push_back(me_r);       
                }
            }
            
            return me_results;
        }

    private:
        void load_frame(u8 *frame, const char *fname) {
            FILE *f = fopen(fname, "rb");
            if (!f || fread(frame, sizeof(u8), width*height, f) != (size_t) width*height) {
		fprintf(stderr, "failed to load frame '%s', exit.\n", fname);
                exit(EXIT_FAILURE);
            }
            
            fclose(f);
        }
    
	// produce copy of an 8x8 pixel block
        void copy_block(u8 block[blocksize][blocksize], u8 *frame, int r, int c) {
            for (int i = 0; i < blocksize; i++) {
                for (int j = 0; j < blocksize; j++) {            
                    block[i][j] = frame[(r + i)*width + c + j];
                }
            }
        }

	// compute best estimate for block at r/c within search range
	// return cost and bestr/bestc
        unsigned int best_estimate(int r, int c, int &bestr, int &bestc, int search) {
            unsigned int best = UINT_MAX;
            for (int i = max(0,r-search); i < min(height-blocksize,r+search); i++) {
                for (int j = max(0,c-search); j < min(width-blocksize,c+search); j++) {    
                    u8 block_ref[blocksize][blocksize]; 
                    copy_block(block_ref, frame_ref, r, c);
                    u8 block[blocksize][blocksize];
                    copy_block(block, frame, i, j);
                    unsigned int cost = sad(block_ref, block);
                    if (cost < best) {
                        bestr = i;
                        bestc = j;
                        best = cost;
                    }
                }
            }
            return best;
        }
    
	// compute sum of absolute difference between blocks
        unsigned int sad(u8 block_ref[blocksize][blocksize], u8 block[blocksize][blocksize]) {
            unsigned int sum = 0;

            for (int by = 0; by < blocksize; by++) {
                for (int bx = 0; bx < blocksize; bx++) {
                    int pixel = block[by][bx];
                    int pixel_ref = block_ref[by][bx];
                    sum += std::abs(pixel - pixel_ref);
                }
            }
            
            return sum;
        }

        const int width, height;
        const int search;
        u8 *frame;
        u8 *frame_ref;
};

int main() {
    VideoCodec vc(720, 576, 16);
    
    VideoCodec::me_results_t *me_results = vc.motion_estimation();
    unsigned int total_cost = 0;
    
    // compute total cost for frame (sum of per block cost)
    for (VideoCodec::me_results_t::iterator it = me_results->begin(); it != me_results->end(); it++)
        total_cost += it->cost;
    delete me_results;

    printf("total SAD = %d\n", total_cost);

    return EXIT_SUCCESS;
}
