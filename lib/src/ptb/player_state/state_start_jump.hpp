/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class describing the state where the player prepare
 * a horizontal jump.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_STATE_START_JUMP_HPP__
#define __PTB_STATE_START_JUMP_HPP__

#include "ptb/player_state/state_player.hpp"

namespace ptb
{
  /**
   * \brief The class describing a state where the player jump.
   * \author Sebastien Angibaud
   */
  class state_start_jump : public state_player
  {
  public:
    /** \brief The type of the parent class. */
    typedef state_player super;

  public:
    state_start_jump(const player_proxy& player);

    virtual std::string get_name() const;
    virtual void progress_spot();

    virtual void do_stop_vertical_jump();
    virtual void do_move_left();
    virtual void do_move_right();
    virtual void do_stop_look_upward();
  }; // class state_start_jump
} // namespace ptb

#endif // __PTB_STATE_START_JUMP_HPP__
