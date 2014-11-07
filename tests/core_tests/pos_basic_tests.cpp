// Copyright (c) 2012-2013 The Boolberry developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chaingen.h"
#include "chaingen_tests_list.h"

#include "pos_basic_tests.h"

using namespace epee;
using namespace currency;


gen_pos_basic_tests::gen_pos_basic_tests()
{
  REGISTER_CALLBACK_METHOD(gen_pos_basic_tests, configure_core);
}
#define FIRST_ALIAS_NAME "first"
#define SECOND_ALIAS_NAME "second"

bool gen_pos_basic_tests::generate(std::vector<test_event_entry>& events) const
{
  uint64_t ts_start = 1338224400;
  std::list<currency::account_base> coin_stake_sources;

  GENERATE_ACCOUNT(miner_account);
  coin_stake_sources.push_back(miner_account);
  MAKE_GENESIS_BLOCK(events, blk_0, miner_account, ts_start);
  MAKE_ACCOUNT(events, first_acc);
  MAKE_ACCOUNT(events, second_acc);
  MAKE_ACCOUNT(events, third_acc);
  DO_CALLBACK(events, "configure_core");


  MAKE_NEXT_BLOCK(events, blk_1, blk_0, miner_account);
  REWIND_BLOCKS_N(events, blk_11, blk_1, miner_account, 10);
  MAKE_NEXT_POS_BLOCK(events, blk_12, blk_11, miner_account, coin_stake_sources);



  return true;
}

bool gen_pos_basic_tests::configure_core(currency::core& c, size_t ev_index, const std::vector<test_event_entry>& events)
{
  currency::pos_config pc = get_default_pos_config();
  pc.min_coinage = DIFFICULTY_POW_TARGET * 10; //four blocks
  c.get_blockchain_storage().set_pos_config(pc);
  return true;
}