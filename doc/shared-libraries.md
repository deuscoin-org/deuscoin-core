Shared Libraries
================

## deuscoinconsensus

The purpose of this library is to make the verification functionality that is critical to Deuscoin's consensus available to other applications, e.g. to language bindings.

### API

The interface is defined in the C header `deuscoinconsensus.h` located in  `src/script/deuscoinconsensus.h`.

#### Version

`deuscoinconsensus_version` returns an `unsigned int` with the the API version *(currently at an experimental `0`)*.

#### Script Validation

`deuscoinconsensus_verify_script` returns an `int` with the status of the verification. It will be `1` if the input script correctly spends the previous output `scriptPubKey`.

##### Parameters
- `const unsigned char *scriptPubKey` - The previous output script that encumbers spending.
- `unsigned int scriptPubKeyLen` - The number of bytes for the `scriptPubKey`.
- `const unsigned char *txTo` - The transaction with the input that is spending the previous output.
- `unsigned int txToLen` - The number of bytes for the `txTo`.
- `unsigned int nIn` - The index of the input in `txTo` that spends the `scriptPubKey`.
- `unsigned int flags` - The script validation flags *(see below)*.
- `deuscoinconsensus_error* err` - Will have the error/success code for the operation *(see below)*.

##### Script Flags
- `deuscoinconsensus_SCRIPT_FLAGS_VERIFY_NONE`
- `deuscoinconsensus_SCRIPT_FLAGS_VERIFY_P2SH` - Evaluate P2SH ([BIP16](https://github.com/deuscoin/bips/blob/master/bip-0016.mediawiki)) subscripts
- `deuscoinconsensus_SCRIPT_FLAGS_VERIFY_DERSIG` - Enforce strict DER ([BIP66](https://github.com/deuscoin/bips/blob/master/bip-0066.mediawiki)) compliance

##### Errors
- `deuscoinconsensus_ERR_OK` - No errors with input parameters *(see the return value of `deuscoinconsensus_verify_script` for the verification status)*
- `deuscoinconsensus_ERR_TX_INDEX` - An invalid index for `txTo`
- `deuscoinconsensus_ERR_TX_SIZE_MISMATCH` - `txToLen` did not match with the size of `txTo`
- `deuscoinconsensus_ERR_DESERIALIZE` - An error deserializing `txTo`

### Example Implementations
- [NDeuscoin](https://github.com/NicolasDorier/NDeuscoin/blob/master/NDeuscoin/Script.cs#L814) (.NET Bindings)
- [node-libdeuscoinconsensus](https://github.com/bitpay/node-libdeuscoinconsensus) (Node.js Bindings)
- [java-libdeuscoinconsensus](https://github.com/dexX7/java-libdeuscoinconsensus) (Java Bindings)
- [deuscoinconsensus-php](https://github.com/Bit-Wasp/deuscoinconsensus-php) (PHP Bindings)
