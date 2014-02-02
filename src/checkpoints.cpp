// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Copyright (c) 2013 JKC Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //

	// no checkpoint now, can be added in later releases
    static MapCheckpoints mapCheckpoints =
            boost::assign::map_list_of
            (  1, uint256("0x11b82349e53d49a5b5ef6262c262564e7663d8cfd912b0040b33683f623022f2"))
            ( 11, uint256("0xc8fc42e967eebdeafcabbd9050a545617f8685d53f2ebcd8f0fa5002b7e62a86"))
            ( 59, uint256("0xcdde8a3e42fa8888df2db8bf6673b29f5e2ae29951275d452686c47acb51cb66"))
            (104, uint256("0x206fe8cc678598456a11041fac65c8e096d9e26c887e391977fdad41e7add208"))
            (10000, uint256("0x7ddbb237b18ffedfa1680a0560d135a9bca247654ab3eef1cc5a39c33074f364"))
            (30030, uint256("0x895f2c50bdf86c3446712d6ff3da448d32e3803a09cb438ad784dbac5c1baf64"))
            (50005, uint256("0xb43e13a918dd208a58fd42aae6aeb51a42e24631cdeb89b2307b62d5353513b9"))
            (100000, uint256("0xfa2e00373495d1343687146a9ef604d8b0f3ee0c21ea749cef9e4c9efaf7c00d"))
            (135000, uint256("0x6ef258d60b6bf2466ade47812d624ca401964d32d264063b2bda3129873d8c26"))
            
			;
        /*
        boost::assign::map_list_of
        (     1, uint256("0x000000552acd41b1f9ae21fc7eb4054dce1331c8755f37f3d30a15825f695cd4"))
        (     2, uint256("0x000008559730ac71244fcca965c73077616a3cebff5e28dadeb61e8ddae631ae"))
        (  1500, uint256("0x841a2965955dd288cfa707a755d05a54e45f8bd476835ec9af4402a2b59a2967"))
        (  4032, uint256("0x9ce90e427198fc0ef05e5905ce3503725b80e26afd35a987965fd7e3d9cf0846"))
        (  8064, uint256("0xeb984353fc5190f210651f150c40b8a4bab9eeeff0b729fcb3987da694430d70"))
        ( 16128, uint256("0x602edf1859b7f9a6af809f1d9b0e6cb66fdc1d4d9dcd7a4bec03e12a1ccd153d"))
        ( 23420, uint256("0xd80fdf9ca81afd0bd2b2a90ac3a9fe547da58f2530ec874e978fce0b5101b507"))
        ( 50000, uint256("0x69dc37eb029b68f075a5012dcc0419c127672adb4f3a32882b2b3e71d07a20a6"))
        ( 80000, uint256("0x4fcb7c02f676a300503f49c764a89955a8f920b46a8cbecb4867182ecdb2e90a"))
        (120000, uint256("0xbd9d26924f05f6daa7f0155f32828ec89e8e29cee9e7121b026a7a3552ac6131"))
        (161500, uint256("0xdbe89880474f4bb4f75c227c77ba1cdc024991123b28b8418dbbf7798471ff43"))
        (179620, uint256("0x2ad9c65c990ac00426d18e446e0fd7be2ffa69e9a7dcb28358a50b2b78b9f709"))
        ;
        */

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
		// return true;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
	
        return mapCheckpoints.rbegin()->first;
		// return 0;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
				// return NULL;
        }
        return NULL;
    }
}
