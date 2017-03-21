// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Deuscoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"
#include "arith_uint256.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Drudge 20170304 TRUMP: OBAMA BUGGED THE TOWER";
    const CScript genesisOutputScript = CScript() << ParseHex("04a69b3f95af2c76f00001c331f1ae7b3074c40e63ef0bc78df9cefc5752eae664be7869c9c1db8da9dd9c6b437f76847ba5ae839df6ae3cbf846fcfc2e754c5f2") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 210000;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = 227931;
        consensus.BIP34Hash = uint256S("0x000000000000024b89b42a942fe0d9fea3bb44ab7bd1b19115dd6a759c0808b8");
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 1 * 1 * 5 * 60; // five minutes
        consensus.nPowTargetSpacing = 1 * 60;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1916; // 95% of 2016
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1462060800; // May 1st, 2016
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1493596800; // May 1st, 2017

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0x9e;
        pchMessageStart[1] = 0xe8;
        pchMessageStart[2] = 0xbc;
        pchMessageStart[3] = 0x5a;
        vAlertPubKey = ParseHex("04b508687ee58913f39c33a5484cbbf8d7ea73dda4cedfbab56a7fb61dea97590a400000702245606b893034c4e5498048ee8a0ea2610c11c110c301ee64e8833f");
        nDefaultPort = 19697;
        nMaxTipAge = 24 * 60 * 60;
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1488633816, 1661610, 0x1e0ffff0, 1, 50 * COIN);



        unsigned int nProofOfWorkLimit = UintToArith256(consensus.powLimit).GetCompact();

        
        consensus.hashGenesisBlock = uint256S("00000bd8de24fb88c5579a9d90cdee14090ac5d39e3105e2878696f684fc7987");


if (true && genesis.GetHash() != consensus.hashGenesisBlock)
{
    LogPrintf("recalculating params for mainnet.\n");
    LogPrintf("old mainnet genesis nonce: 0x%x\n", genesis.nNonce);
    LogPrintf("old mainnet genesis hash:  %s\n", consensus.hashGenesisBlock.ToString());
    LogPrintf("Calc mainnet genesis hash: %s\n", genesis.GetHash().ToString());
    LogPrintf("old mainnet consensus.powLimit:  %s\n", consensus.powLimit.ToString());        
    LogPrintf("Calculating mainnet genesis hash\n");
    
    for(genesis.nNonce = 0; UintToArith256(genesis.GetHash()).GetCompact() > nProofOfWorkLimit; genesis.nNonce++){
//         LogPrintf("nonce: 0x%x\n", genesis.nNonce);
//         LogPrintf("Hash : 0x%x\n", UintToArith256(genesis.GetHash()).GetCompact());
//         LogPrintf("Limit: 0x%x\n", nProofOfWorkLimit);
//         LogPrintf("=====================================================================================\n");
    }

    LogPrintf("new mainnet genesis merkle root: %s\n", genesis.hashMerkleRoot.ToString());
    LogPrintf("new mainnet genesis nonce      : 0x%x\n", genesis.nNonce);
    LogPrintf("new mainnet genesis hash       : %s\n", genesis.GetHash().ToString());
    LogPrintf("mainnet consensus.powLimit     :  %s\n", consensus.powLimit.ToString());        

}

                
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000bd8de24fb88c5579a9d90cdee14090ac5d39e3105e2878696f684fc7987"));
        assert(genesis.hashMerkleRoot == uint256S("0xe4be3b5119b7540543c5fe3bce2a5e104880227d8bd0f349bdbe82dfcf5759e2"));

        vFixedSeeds.clear();
        vSeeds.clear();

        vSeeds.push_back(CDNSSeedData("explorer.deuscoin.org", "52.221.223.83")); // block explorer
//         vSeeds.push_back(CDNSSeedData("bluematt.me", "dnsseed.bluematt.me")); // Matt Corallo
//         vSeeds.push_back(CDNSSeedData("dashjr.org", "dnsseed.deuscoin.dashjr.org")); // Luke Dashjr
//         vSeeds.push_back(CDNSSeedData("deuscoinstats.com", "seed.deuscoinstats.com")); // Christian Decker
//         vSeeds.push_back(CDNSSeedData("xf2.org", "bitseed.xf2.org")); // Jeff Garzik
//         vSeeds.push_back(CDNSSeedData("deuscoin.jonasschnelli.ch", "seed.deuscoin.jonasschnelli.ch")); // Jonas Schnelli

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,30);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,35);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,128);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            ( 0, uint256S("0x00000bd8de24fb88c5579a9d90cdee14090ac5d39e3105e2878696f684fc7987"))
            ( 100, uint256S("0x0000000e94cc6cbba3024bfb3cb7083275cf2f4bf3d8782c7e1bd1951cf9dbf4"))
            ( 1000, uint256S("0x00000065cb647f3c6c960c86c8a0d2ce9abc4697db03a1efc6d0df202f3279d8"))
            ( 10000, uint256S("0x00000025c4fc69fefb0a080c6547e11bf0e865031505ff6528b234ea20694aee"))
            ,
            1489682494, // * UNIX timestamp of last checkpoint block
            0,   // * total number of transactions between genesis and last checkpoint
                        //   (the tx=... number in the SetBestChain debug.log lines)
            500.0     // * estimated number of transactions per day after checkpoint
        };
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 210000;
        consensus.nMajorityEnforceBlockUpgrade = 51;
        consensus.nMajorityRejectBlockOutdated = 75;
        consensus.nMajorityWindow = 100;
        consensus.BIP34Height = 21111;
        consensus.BIP34Hash = uint256S("0x0000000023b3a96d3484e5abb3755c413e7d41500f8e2a5c3f0dd01299cd8ef8");
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 1 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1456790400; // March 1st, 2016
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1493596800; // May 1st, 2017

        pchMessageStart[0] = 0xd3;
        pchMessageStart[1] = 0xe4;
        pchMessageStart[2] = 0xcf;
        pchMessageStart[3] = 0x9a;
        vAlertPubKey = ParseHex("04a69b3f95af2c76f00001c331f1ae7b3074c40e63ef0bc78df9cefc5752eae664be7869c9c1db8da9dd9c6b437f76847ba5ae839df6ae3cbf846fcfc2e754c5f2");
        nDefaultPort = 29666;
        nMaxTipAge = 0x7fffffff;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1488633817, 1391799723, 0x1e0ffff0, 1, 50 * COIN);
        
        unsigned int nProofOfWorkLimit = UintToArith256(consensus.powLimit).GetCompact();

        
        consensus.hashGenesisBlock = uint256S("00000c6d73c1e3cb85c905e0d59859eca8f0728dca89c23405abe6a49343c320");



if (true && genesis.GetHash() != consensus.hashGenesisBlock)
{
    LogPrintf("recalculating params for testnet.\n");
    LogPrintf("old testnet genesis nonce: 0x%x\n", genesis.nNonce);
    LogPrintf("old testnet genesis hash:  %s\n", consensus.hashGenesisBlock.ToString());
    LogPrintf("Calc testnet genesis hash: %s\n", genesis.GetHash().ToString());
    LogPrintf("old testnet consensus.powLimit:  %s\n", consensus.powLimit.ToString());        
    LogPrintf("Calculating testnet genesis hash\n");
    
    for(genesis.nNonce = 0; UintToArith256(genesis.GetHash()).GetCompact() > nProofOfWorkLimit; genesis.nNonce++){
//         LogPrintf("nonce: 0x%x\n", genesis.nNonce);
    }

    LogPrintf("new testnet genesis merkle root: %s\n", genesis.hashMerkleRoot.ToString());
    LogPrintf("new testnet genesis nonce: 0x%x\n", genesis.nNonce);
    LogPrintf("new testnet genesis hash: %s\n", genesis.GetHash().ToString());
}

        
        
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000c6d73c1e3cb85c905e0d59859eca8f0728dca89c23405abe6a49343c320"));
        assert(genesis.hashMerkleRoot == uint256S("0xe4be3b5119b7540543c5fe3bce2a5e104880227d8bd0f349bdbe82dfcf5759e2"));

        vFixedSeeds.clear();
        vSeeds.clear();
//         vSeeds.push_back(CDNSSeedData("deuscoin.petertodd.org", "testnet-seed.deuscoin.petertodd.org"));
//         vSeeds.push_back(CDNSSeedData("bluematt.me", "testnet-seed.bluematt.me"));
//         vSeeds.push_back(CDNSSeedData("deuscoin.schildbach.de", "testnet-seed.deuscoin.schildbach.de"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            ( 0, uint256S("0x00000c6d73c1e3cb85c905e0d59859eca8f0728dca89c23405abe6a49343c320")),
            1488633817,
            0,
            250
        };

    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = -1; // BIP34 has not necessarily activated on regtest
        consensus.BIP34Hash = uint256();
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 1 * 1 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 1 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;

        pchMessageStart[0] = 0x3f;
        pchMessageStart[1] = 0x3d;
        pchMessageStart[2] = 0x53;
        pchMessageStart[3] = 0x3e;
        nMaxTipAge = 24 * 60 * 60;
        nDefaultPort = 18444;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1485507504, 3, 0x207fffff, 1, 50 * COIN);
        unsigned int nProofOfWorkLimit = UintToArith256(consensus.powLimit).GetCompact();

        
        consensus.hashGenesisBlock = uint256S("73b656e9712cbb792547fcfc87b77c232b5001ec0c101b2ba91150dddabd4070");



if (true && genesis.GetHash() != consensus.hashGenesisBlock)
{
    LogPrintf("recalculating params for regnet.\n");
    LogPrintf("old regnet genesis nonce: 0x%x\n", genesis.nNonce);
    LogPrintf("old regnet genesis hash:  %s\n", consensus.hashGenesisBlock.ToString());
    LogPrintf("Calc regnet genesis hash: %s\n", genesis.GetHash().ToString());
    LogPrintf("old regnet consensus.powLimit:  %s\n", consensus.powLimit.ToString());        
    LogPrintf("Calculating regnet genesis hash\n");
    
    for(genesis.nNonce = 0; UintToArith256(genesis.GetHash()).GetCompact() > nProofOfWorkLimit; genesis.nNonce++){
//         LogPrintf("nonce: 0x%x\n", genesis.nNonce);
    }

    LogPrintf("new regnet genesis merkle root: %s\n", genesis.hashMerkleRoot.ToString());
    LogPrintf("new regnet genesis nonce: 0x%x\n", genesis.nNonce);
    LogPrintf("new regnet genesis hash: %s\n", genesis.GetHash().ToString());
}

        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x73b656e9712cbb792547fcfc87b77c232b5001ec0c101b2ba91150dddabd4070"));
        assert(genesis.hashMerkleRoot == uint256S("0xe4be3b5119b7540543c5fe3bce2a5e104880227d8bd0f349bdbe82dfcf5759e2"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        checkpointData = (CCheckpointData){
            boost::assign::map_list_of
            ( 0, uint256S("0x73b656e9712cbb792547fcfc87b77c232b5001ec0c101b2ba91150dddabd4070")),
            0,
            0,
            0
        };
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
    }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
            return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
            return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
            return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}
