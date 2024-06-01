# Copyright (c) 2013-2016 The Bitcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

DIST_SUBDIRS = secp256k1 univalue chiabls

AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS) $(GPROF_LDFLAGS) $(SANITIZER_LDFLAGS)
AM_CXXFLAGS = $(DEBUG_CXXFLAGS) $(HARDENED_CXXFLAGS) $(WARN_CXXFLAGS) $(NOWARN_CXXFLAGS) $(ERROR_CXXFLAGS) $(GPROF_CXXFLAGS) $(SANITIZER_CXXFLAGS)
AM_CPPFLAGS = $(DEBUG_CPPFLAGS) $(HARDENED_CPPFLAGS)
AM_LIBTOOLFLAGS = --preserve-dup-deps
EXTRA_LIBRARIES =

if EMBEDDED_UNIVALUE
LIBUNIVALUE = univalue/libunivalue.la

$(LIBUNIVALUE): $(wildcard univalue/lib/*) $(wildcard univalue/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)
else
LIBUNIVALUE = $(UNIVALUE_LIBS)
endif

MUBDI_CONFIG_INCLUDES=-I$(builddir)/config
MUBDI_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BDB_CPPFLAGS) $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS)

MUBDI_INCLUDES += -I$(srcdir)/secp256k1/include
MUBDI_INCLUDES += -I$(srcdir)/chiabls/src
MUBDI_INCLUDES += -I$(srcdir)/chiabls/contrib/relic/include
MUBDI_INCLUDES += $(UNIVALUE_CFLAGS)

LIBMUBDI_SERVER=libmubdi_server.a
LIBMUBDI_COMMON=libmubdi_common.a
LIBMUBDI_CLI=libmubdi_cli.a
LIBMUBDI_UTIL=libmubdi_util.a
LIBMUBDI_CRYPTO=crypto/libmubdi_crypto.a
LIBMUBDI_AIRLOGIC=libairlogic/libmubdi_airlogic.a
LIBMUBDIQT=qt/libmubdiqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la
LIBCHIABLS=chiabls/libchiabls.la

if ENABLE_ZMQ
LIBMUBDI_ZMQ=libmubdi_zmq.a
endif
if BUILD_MUBDI_LIBS
LIBMUBDICONSENSUS=libmubdiconsensus.la
endif
if ENABLE_WALLET
LIBMUBDI_WALLET=libmubdi_wallet.a
endif

BLS_LIBS = $(LIBCHIABLS)

$(LIBSECP256K1): $(wildcard secp256k1/src/*.h) $(wildcard secp256k1/src/*.c) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

$(LIBCHIABLS):
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C chiabls

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES += \
  $(LIBMUBDI_CRYPTO) \
  $(LIBMUBDI_UTIL) \
  $(LIBMUBDI_COMMON) \
  $(LIBMUBDI_AIRLOGIC) \
  $(LIBMUBDI_SERVER) \
  $(LIBMUBDI_CLI) \
  $(LIBMUBDI_WALLET) \
  $(LIBMUBDI_ZMQ)

lib_LTLIBRARIES = $(LIBMUBDICONSENSUS)

bin_PROGRAMS =
noinst_PROGRAMS =
TESTS =
BENCHMARKS =

if BUILD_MUBDID
  bin_PROGRAMS += mtkd
endif

if BUILD_MUBDI_UTILS
  bin_PROGRAMS += mtk-cli mubdi-tx
endif

.PHONY: FORCE check-symbols check-security
# mubdi core #
MUBDI_CORE_H = \
  activemasternode.h \
  addrdb.h \
  addrman.h \
  attributes.h \
  arith_uint256.h \
  amount.h \
  base58.h \
  bip38.h \
  bloom.h \
  blocksignature.h \
  bls/bls_ies.h \
  bls/bls_worker.h \
  bls/bls_wrapper.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  coincontrol.h \
  coins.h \
  compat.h \
  compat/byteswap.h \
  compat/cpuid.h \
  compat/endian.h \
  compat/sanity.h \
  compressor.h \
  consensus/consensus.h \
  consensus/merkle.h \
  consensus/validation.h \
  consensus/tx_verify.h \
  consensus/params.h \
  consensus/upgrades.h \
  primitives/block.h \
  primitives/transaction.h \
  core_io.h \
  cuckoocache.h \
  crypter.h \
  ctpl.h \
  cyclingvector.h \
  evo/evodb.h \
  evo/evonotificationinterface.h \
  addressbook.h \
  wallet/db.h \
  flatfile.h \
  fs.h \
  hash.h \
  httprpc.h \
  httpserver.h \
  indirectmap.h \
  init.h \
  interfaces/handler.h \
  interfaces/wallet.h \
  legacy/stakemodifier.h \
  kernel.h \
  key.h \
  key_io.h \
  keystore.h \
  dbwrapper.h \
  limitedmap.h \
  logging.h \
  budget/budgetdb.h \
  budget/budgetmanager.h \
  budget/budgetproposal.h \
  budget/budgetvote.h \
  budget/finalizedbudget.h \
  budget/finalizedbudgetvote.h \
  budget/budgetutil.h \
  mapport.h \
  memusage.h \
  masternode.h \
  masternode-payments.h \
  masternode-sync.h \
  masternodeman.h \
  masternodeconfig.h \
  merkleblock.h \
  messagesigner.h \
  blockassembler.h \
  miner.h \
  moneysupply.h \
  net.h \
  net_processing.h \
  netaddress.h \
  netbase.h \
  netmessagemaker.h \
  noui.h \
  policy/feerate.h \
  policy/fees.h \
  policy/policy.h \
  optional.h \
  operationresult.h \
  pow.h \
  prevector.h \
  protocol.h \
  pubkey.h \
  random.h \
  randomenv.h \
  reverse_iterate.h \
  rpc/client.h \
  rpc/protocol.h \
  rpc/register.h \
  rpc/server.h \
  saltedhasher.h \
  scheduler.h \
  script/interpreter.h \
  script/keyorigin.h \
  script/script.h \
  script/sigcache.h \
  script/sign.h \
  script/standard.h \
  script/script_error.h \
  serialize.h \
  shutdown.h \
  span.h \
  spork.h \
  sporkdb.h \
  sporkid.h \
  stakeinput.h \
  script/ismine.h \
  streams.h \
  support/allocators/mt_pooled_secure.h \
  support/allocators/pooled_secure.h \
  support/allocators/secure.h \
  support/allocators/zeroafterfree.h \
  support/cleanse.h \
  support/events.h \
  support/lockedpool.h \
  sync.h \
  threadsafety.h \
  threadinterrupt.h \
  timedata.h \
  tinyformat.h \
  torcontrol.h \
  txdb.h \
  txmempool.h \
  guiinterface.h \
  guiinterfaceutil.h \
  uint256.h \
  undo.h \
  util/asmap.h \
  util/blockstatecatcher.h \
  util/system.h \
  util/macros.h \
  util/string.h \
  util/threadnames.h \
  util/validation.h \
  utilstrencodings.h \
  utilmoneystr.h \
  utiltime.h \
  util/vector.h \
  validation.h \
  validationinterface.h \
  version.h \
  wallet/hdchain.h \
  wallet/rpcwallet.h \
  wallet/scriptpubkeyman.h \
  destination_io.h \
  wallet/fees.h \
  wallet/init.h \
  wallet/wallet.h \
  wallet/walletdb.h \
  wallet/walletutil.h \
  warnings.h \
  zmq/zmqabstractnotifier.h \
  zmq/zmqconfig.h \
  zmq/zmqnotificationinterface.h \
  zmq/zmqpublishnotifier.h

obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh "$(abs_top_builddir)/src/obj/build.h" \
	  "$(abs_top_srcdir)"
libmubdi_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between mubdid and mubdi-qt
libmubdi_server_a_CPPFLAGS = $(AM_CPPFLAGS) $(MUBDI_INCLUDES) $(MINIUPNPC_CPPFLAGS) $(NATPMP_CPPFLAGS) $(EVENT_CFLAGS) $(EVENT_PTHREADS_CFLAGS)
libmubdi_server_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libmubdi_server_a_SOURCES = \
  addrdb.cpp \
  addrman.cpp \
  bloom.cpp \
  blocksignature.cpp \
  bls/bls_ies.cpp \
  bls/bls_worker.cpp \
  bls/bls_wrapper.cpp \
  chain.cpp \
  checkpoints.cpp \
  consensus/params.cpp \
  consensus/tx_verify.cpp \
  flatfile.cpp \
  evo/evodb.cpp \
  evo/evonotificationinterface.cpp \
  httprpc.cpp \
  httpserver.cpp \
  init.cpp \
  dbwrapper.cpp \
  merkleblock.cpp \
  mapport.cpp \
  miner.cpp \
  net.cpp \
  net_processing.cpp \
  noui.cpp \
  policy/fees.cpp \
  policy/policy.cpp \
  pow.cpp \
  rest.cpp \
  rpc/blockchain.cpp \
  rpc/masternode.cpp \
  rpc/budget.cpp \
  rpc/mining.cpp \
  rpc/misc.cpp \
  rpc/net.cpp \
  rpc/rawtransaction.cpp \
  rpc/server.cpp \
  script/sigcache.cpp \
  script/ismine.cpp \
  shutdown.cpp \
  sporkdb.cpp \
  timedata.cpp \
  torcontrol.cpp \
  txdb.cpp \
  txmempool.cpp \
  validation.cpp \
  validationinterface.cpp \
  $(MUBDI_CORE_H)

if ENABLE_ZMQ
libmubdi_zmq_a_CPPFLAGS = $(MUBDI_INCLUDES) $(ZMQ_CFLAGS)
libmubdi_zmq_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libmubdi_zmq_a_SOURCES = \
  zmq/zmqabstractnotifier.cpp \
  zmq/zmqnotificationinterface.cpp \
  zmq/zmqpublishnotifier.cpp
endif

# wallet: shared between mubdid and mubdi-qt, but only linked
# when wallet enabled
libmubdi_wallet_a_CPPFLAGS = $(AM_CPPFLAGS) $(MUBDI_INCLUDES)
libmubdi_wallet_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libmubdi_wallet_a_SOURCES = \
  bip38.cpp \
  interfaces/wallet.cpp \
  addressbook.cpp \
  crypter.cpp \
  legacy/stakemodifier.cpp \
  kernel.cpp \
  wallet/db.cpp \
  wallet/fees.cpp \
  wallet/init.cpp \
  wallet/rpcdump.cpp \
  wallet/rpcwallet.cpp \
  wallet/hdchain.cpp \
  wallet/scriptpubkeyman.cpp \
  destination_io.cpp \
  wallet/wallet.cpp \
  wallet/walletdb.cpp \
  wallet/walletutil.cpp \
  stakeinput.cpp \
  $(MUBDI_CORE_H)

# crypto primitives library
crypto_libmubdi_crypto_a_CPPFLAGS = $(AM_CPPFLAGS) $(PIC_FLAGS)
crypto_libmubdi_crypto_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIC_FLAGS)
crypto_libmubdi_crypto_a_SOURCES = \
  crypto/aes.cpp \
  crypto/aes.h \
  crypto/sha1.cpp \
  crypto/sha256.cpp \
  crypto/sha512.cpp \
  crypto/chacha20.h \
  crypto/chacha20.cpp \
  crypto/hmac_sha256.cpp \
  crypto/rfc6979_hmac_sha256.cpp \
  crypto/hmac_sha512.cpp \
  crypto/scrypt.cpp \
  crypto/ripemd160.cpp \
  crypto/sph_md_helper.c \
  crypto/sph_sha2big.c \
  crypto/aes_helper.c \
  crypto/blake.c \
  crypto/bmw.c \
  crypto/groestl.c \
  crypto/jh.c \
  crypto/luffa.c \
  crypto/keccak.c \
  crypto/skein.c \
  crypto/cubehash.c \
  crypto/shavite.c \
  crypto/shabal.c \
  crypto/simd.c \
  crypto/echo.c \
  crypto/whirlpool.c \
  crypto/haval.c \
  crypto/hamsi.c \
  crypto/fugue.c \
  crypto/sha2.c \
  crypto/common.h \
  crypto/sha256.h \
  crypto/sha3.h \
  crypto/sha3.cpp \
  crypto/sha512.h \
  crypto/siphash.cpp \
  crypto/siphash.h \
  crypto/hmac_sha256.h \
  crypto/rfc6979_hmac_sha256.h \
  crypto/hmac_sha512.h \
  crypto/scrypt.h \
  crypto/sha1.h \
  crypto/ripemd160.h \
  crypto/sph_blake.h \
  crypto/sph_bmw.h \
  crypto/sph_groestl.h \
  crypto/sph_jh.h \
  crypto/sph_keccak.h \
  crypto/sph_luffa.h \
  crypto/sph_shavite.h \
  crypto/sph_hamsi.h \
  crypto/sph_cubehash.h \
  crypto/sph_skein.h \
  crypto/sph_simd.h \
  crypto/sph_fugue.h \
  crypto/sph_echo.h \
  crypto/sph_shabal.h \
  crypto/sph_whirlpool.h \
  crypto/sph_sha2.h \
  crypto/sph_haval.h \
  crypto/sph_types.h

# libairlogic library
libairlogic_libmubdi_airlogic_a_CPPFLAGS = $(AM_CPPFLAGS) $(BOOST_CPPFLAGS)
libairlogic_libmubdi_airlogic_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libairlogic_libmubdi_airlogic_a_SOURCES = \
  libairlogic/bignum.h\
  libairlogic/bignum.cpp

# common: shared between mubdid, and mubdi-qt and non-server tools
libmubdi_common_a_CPPFLAGS = $(AM_CPPFLAGS) $(MUBDI_INCLUDES)
libmubdi_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libmubdi_common_a_SOURCES = \
  activemasternode.cpp \
  base58.cpp \
  bip38.cpp \
  budget/budgetdb.cpp \
  budget/budgetmanager.cpp \
  budget/budgetproposal.cpp \
  budget/budgetvote.cpp \
  budget/finalizedbudget.cpp \
  budget/finalizedbudgetvote.cpp \
  budget/budgetutil.cpp \
  chainparams.cpp \
  consensus/upgrades.cpp \
  coins.cpp \
  compressor.cpp \
  consensus/merkle.cpp \
  key_io.cpp \
  primitives/block.cpp \
  primitives/transaction.cpp \
  core_read.cpp \
  core_write.cpp \
  hash.cpp \
  key.cpp \
  keystore.cpp \
  masternode.cpp \
  masternode-payments.cpp \
  masternode-sync.cpp \
  masternodeconfig.cpp \
  masternodeman.cpp \
  messagesigner.cpp \
  netaddress.cpp \
  netbase.cpp \
  policy/feerate.cpp \
  protocol.cpp \
  pubkey.cpp \
  saltedhasher.cpp \
  scheduler.cpp \
  script/interpreter.cpp \
  script/script.cpp \
  script/sign.cpp \
  script/standard.cpp \
  tiertwo_networksync.cpp \
  warnings.cpp \
  script/script_error.cpp \
  spork.cpp \
  sporkdb.cpp \
  $(MUBDI_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libmubdi_util_a_CPPFLAGS = $(AM_CPPFLAGS) $(MUBDI_INCLUDES)
libmubdi_util_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libmubdi_util_a_SOURCES = \
  arith_uint256.cpp \
  chainparamsbase.cpp \
  clientversion.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  compat/strnlen.cpp \
  fs.cpp \
  interfaces/handler.cpp \
  logging.cpp \
  random.cpp \
  randomenv.cpp \
  rpc/protocol.cpp \
  support/cleanse.cpp \
  support/lockedpool.cpp \
  sync.cpp \
  threadinterrupt.cpp \
  util/asmap.cpp \
  uint256.cpp \
  util/system.cpp \
  utilmoneystr.cpp \
  util/threadnames.cpp \
  utilstrencodings.cpp \
  util/string.cpp \
  util/validation.cpp \
  utiltime.cpp \
  $(MUBDI_CORE_H)

if GLIBC_BACK_COMPAT
libmubdi_util_a_SOURCES += compat/glibc_compat.cpp
AM_LDFLAGS += $(COMPAT_LDFLAGS)
endif

# cli: shared between mubdi-cli and mubdi-qt
libmubdi_cli_a_CPPFLAGS = $(AM_CPPFLAGS) $(MUBDI_INCLUDES)
libmubdi_cli_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libmubdi_cli_a_SOURCES = \
  rpc/client.cpp \
  $(MUBDI_CORE_H)

nodist_libmubdi_util_a_SOURCES = $(srcdir)/obj/build.h
#

# mubdid binary #
mtkd_SOURCES = mubdid.cpp
mtkd_CPPFLAGS = $(AM_CPPFLAGS) $(MUBDI_INCLUDES)
mtkd_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
mtkd_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
mtkd_SOURCES += mubdid-res.rc
endif
mtkd_LDADD = \
  $(LIBMUBDI_SERVER) \
  $(LIBMUBDI_WALLET) \
  $(LIBMUBDI_COMMON) \
  $(LIBUNIVALUE) \
  $(LIBMUBDI_AIRLOGIC) \
  $(LIBMUBDI_UTIL) \
  $(LIBMUBDI_ZMQ) \
  $(LIBMUBDI_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBLEVELDB_SSE42) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

mtkd_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(MINIUPNPC_LIBS) $(NATPMP_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS) $(ZMQ_LIBS) $(BLS_LIBS)

# mubdi-cli binary #
mtk_cli_SOURCES = mubdi-cli.cpp
mtk_cli_CPPFLAGS = $(AM_CPPFLAGS) $(MUBDI_INCLUDES) $(EVENT_CFLAGS)
mtk_cli_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
mtk_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
mtk_cli_SOURCES += mubdi-cli-res.rc
endif

mtk_cli_LDADD = \
  $(LIBMUBDI_CLI) \
  $(LIBUNIVALUE) \
  $(LIBMUBDI_UTIL) \
  $(LIBMUBDI_CRYPTO)

mtk_cli_LDADD += $(BOOST_LIBS) $(EVENT_LIBS) $(BLS_LIBS)
#

# mubdi-tx binary #
mubdi_tx_SOURCES = mubdi-tx.cpp
mubdi_tx_CPPFLAGS = $(AM_CPPFLAGS) $(MUBDI_INCLUDES)
mubdi_tx_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
mubdi_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
mubdi_tx_SOURCES += mubdi-tx-res.rc
endif

mubdi_tx_LDADD = \
  $(LIBUNIVALUE) \
  $(LIBMUBDI_COMMON) \
  $(LIBMUBDI_AIRLOGIC) \
  $(LIBMUBDI_UTIL) \
  $(LIBMUBDI_CRYPTO) \
  $(LIBSECP256K1)

mubdi_tx_LDADD += $(BOOST_LIBS) $(BLS_LIBS)
#

# mubdiconsensus library #
if BUILD_MUBDI_LIBS
include_HEADERS = script/mubdiconsensus.h
libmubdiconsensus_la_SOURCES = \
  arith_uint256.cpp \
  primitives/transaction.cpp \
  crypto/hmac_sha512.cpp \
  crypto/scrypt.cpp \
  crypto/sha1.cpp \
  crypto/sha256.cpp \
  crypto/sha512.cpp \
  crypto/ripemd160.cpp \
  hash.cpp \
  pubkey.cpp \
  script/script.cpp \
  script/interpreter.cpp \
  script/mubdiconsensus.cpp \
  uint256.cpp \
  utilstrencodings.cpp

if GLIBC_BACK_COMPAT
  libmubdiconsensus_la_SOURCES += compat/glibc_compat.cpp
endif

libmubdiconsensus_la_LDFLAGS = $(AM_LDFLAGS) -no-undefined $(RELDFLAGS)
libmubdiconsensus_la_LIBADD = $(LIBSECP256K1) $(BLS_LIBS)
libmubdiconsensus_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(builddir)/obj -I$(srcdir)/secp256k1/include -DBUILD_MUBDI_INTERNAL
libmubdiconsensus_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)

endif
#

CLEANFILES = $(EXTRA_LIBRARIES)

CLEANFILES += *.gcda *.gcno
CLEANFILES += budget/*.gcda budget/*.gcno
CLEANFILES += compat/*.gcda compat/*.gcno
CLEANFILES += consensus/*.gcda consensus/*.gcno
CLEANFILES += crc32c/src/*.gcda crc32c/src/*.gcno
CLEANFILES += crypto/*.gcda crypto/*.gcno
CLEANFILES += evo/*.gcda evo/*.gcno
CLEANFILES += interfaces/*.gcda interfaces/*.gcno
CLEANFILES += legacy/*.gcda legacy/*.gcno
CLEANFILES += libairlogic/*.gcda libairlogic/*.gcno
CLEANFILES += policy/*.gcda policy/*.gcno
CLEANFILES += primitives/*.gcda primitives/*.gcno
CLEANFILES += rpc/*.gcda rpc/*.gcno
CLEANFILES += script/*.gcda script/*.gcno
CLEANFILES += support/*.gcda support/*.gcno
CLEANFILES += univalue/*.gcda univalue/*.gcno
CLEANFILES += util/*.gcda util/*.gcno
CLEANFILES += wallet/*.gcda wallet/*.gcno
CLEANFILES += wallet/test/*.gcda wallet/test/*.gcno
CLEANFILES += zmq/*.gcda zmq/*.gcno
CLEANFILES += obj/build.h

CTAES_DIST =  crypto/ctaes/bench.c
CTAES_DIST += crypto/ctaes/ctaes.c
CTAES_DIST += crypto/ctaes/ctaes.h
CTAES_DIST += crypto/ctaes/README.md
CTAES_DIST += crypto/ctaes/test.c

IMMER_DIST = immer

EXTRA_DIST = $(CTAES_DIST)
EXTRA_DIST += $(IMMER_DIST)


config/mubdi-config.h: config/stamp-h1
	@$(MAKE) -C $(top_builddir) $(subdir)/$(@)
config/stamp-h1: $(top_srcdir)/$(subdir)/config/mubdi-config.h.in $(top_builddir)/config.status
	$(AM_V_at)$(MAKE) -C $(top_builddir) $(subdir)/$(@)
$(top_srcdir)/$(subdir)/config/mubdi-config.h.in:  $(am__configure_deps)
	$(AM_V_at)$(MAKE) -C $(top_srcdir) $(subdir)/config/mubdi-config.h.in

clean-local:
	-$(MAKE) -C secp256k1 clean
	-$(MAKE) -C univalue clean
	-$(MAKE) -C chiabls clean
	-rm -f leveldb/*/*.gcda leveldb/*/*.gcno leveldb/helpers/memenv/*.gcda leveldb/helpers/memenv/*.gcno
	-rm -f config.h
	-rm -rf test/__pycache__
	-rm -rf ../target

.rc.o:
	@test -f $(WINDRES)
	## FIXME: How to get the appropriate modulename_CPPFLAGS in here?
	$(AM_V_GEN) $(WINDRES) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(CPPFLAGS) -DWINDRES_PREPROC -i $< -o $@

check-symbols: $(bin_PROGRAMS)
if GLIBC_BACK_COMPAT
	@echo "Checking glibc back compat..."
	$(AM_V_at) READELF=$(READELF) CPPFILT=$(CPPFILT) $(PYTHON) $(top_srcdir)/contrib/devtools/symbol-check.py < $(bin_PROGRAMS)
endif

check-security: $(bin_PROGRAMS)
if HARDEN
	@echo "Checking binary security..."
	$(AM_V_at) READELF=$(READELF) OBJDUMP=$(OBJDUMP) $(PYTHON) $(top_srcdir)/contrib/devtools/security-check.py < $(bin_PROGRAMS)
endif

if EMBEDDED_LEVELDB
include Makefile.crc32c.include
include Makefile.leveldb.include
endif

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_BENCH
include Makefile.bench.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
