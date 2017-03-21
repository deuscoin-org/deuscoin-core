// Copyright (c) 2016 The Deuscoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DEUSCOIN_POLICY_RBF_H
#define DEUSCOIN_POLICY_RBF_H

#include "txmempool.h"

// Check whether the sequence numbers on this transaction are signaling
// opt-in to replace-by-fee, according to BIP 125
bool SignalsOptInRBF(const CTransaction &tx);

// Determine whether an in-mempool transaction is signaling opt-in to RBF
// according to BIP 125
// This involves checking sequence numbers of the transaction, as well
// as the sequence numbers of all in-mempool ancestors.
bool IsRBFOptIn(const CTxMemPoolEntry &entry, CTxMemPool &pool);

#endif // DEUSCOIN_POLICY_RBF_H
