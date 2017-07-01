/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    Encryption / Decryption
    - - - - - - - - - - - - - - - - - - -
    Diogo Pratas        pratas@ua.pt
    Morteza Hosseini    seyedmorteza@ua.pt
    Armando J. Pinho    ap@ua.pt
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#ifndef CRYFA_ENDECRYPTO_H
#define CRYFA_ENDECRYPTO_H

#include "def.h"
using std::string;

class EnDecrypto
{
public:
    EnDecrypto();                                        // constructor
    void compressFA ();                                  // compress FASTA
    void compressFQ ();                                  // compress FASTQ
    void decompress ();                                  // decompress
    
    byte   n_threads;                                    // number of threads
    string inFileName;                                   // input file name
    string keyFileName;                                  // password file name
    bool   verbose = false;                              // for verbose mode
    bool   disable_shuffle = false;                      // disable shuffle
    
private:
    inline void encrypt  ();                             // encrypt
    inline void decrypt  ();                             // decrypt
    inline void decompFA ();                             // decomp. FA
    inline void decompFQ ();                             // decomp. FQ
    inline void buildIV  (byte*, const string&);         // build IV
    inline void buildKey (byte*, const string&);         // build key
    inline void printIV  (byte*)                const;   // print IV
    inline void printKey (byte*)                const;   // print key
    inline string extractPass ()                const;   // extract password
    inline void evalPassSize (const string&)    const;   // evaluate pass size
    inline bool hasFQjustPlus ()                const;   // check '+' line
    inline void gatherHdrQs (string&, string&)  const;   // gather hdrs & qss
    inline std::minstd_rand0 &randomEngine ();           // random no. engine
    inline void my_srand (const ui);                     // random no. seed
    inline int  my_rand ();                              // random no generate
//    inline ull  un_shuffleSeedGen (const ui);            // (un)shuffle seed gen
    inline void un_shuffleSeedGen ();            // (un)shuffle seed gen
    inline void shufflePkd (string&);                    // shuffle packed
    inline void unshufflePkd (string::iterator&, const ull); // unshuffle packed
    inline void pack (const ull, const byte,             // pack
                      string (*)(const string&, const htable_t&),
                      string (*)(const string&, const htable_t&));
    
    string   Hdrs;                                       // max: 39 values
    string   QSs;                                        // max: 39 values
    string   HdrsX;                                      // extended Hdrs
    string   QSsX;                                       // extended QSs
    htable_t HdrMap;                                     // Hdrs hash table
    htable_t QsMap;                                      // QSs hash table
    // check if reading input file reached to the end. MUST be initialized
    bool     isInEmpty = false;
    
    
    ull seed_shared;
};

#endif //CRYFA_ENDECRYPTO_H