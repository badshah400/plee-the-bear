/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::contest_result_effect class.
 * \author Sebastien Angibaud
 */
#include "ptb/transition_effect/contest_result_effect.hpp"
#include "ptb/item/bonus_points/bonus_points.hpp"
#include "ptb/item/bonus_manager.hpp"

#include "engine/game.hpp"
#include "engine/level.hpp"
#include "engine/world.hpp"
#include "visual/scene_sprite.hpp"

#include <libintl.h>

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::contest_result_effect::contest_result_effect()
  : m_world(NULL), m_loser_index(1)
{

} // contest_result_effect::contest_result_effect()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialise the effect.
 */
void ptb::contest_result_effect::build()
{
  super::build();
  set_color(0, 0, 0);
  set_duration(1, 10, 0);

  get_level_globals().stop_all_musics();

  update_bonus_state();

  if ( m_loser_index == 1 )
    {
      m_player_1 = 
        get_level_globals().auto_sprite
        ( "gfx/mini-game/arena/arena-1.png", "player 1 loser" );
       m_player_2 = 
        get_level_globals().auto_sprite
        ( "gfx/mini-game/arena/arena-1.png", "player 2 winner" );
    }
  else
    {
      m_player_1 = 
        get_level_globals().auto_sprite
        ( "gfx/mini-game/arena/arena-1.png", "player 1 winner" );
       m_player_2 = 
        get_level_globals().auto_sprite
        ( "gfx/mini-game/arena/arena-1.png", "player 2 loser" );
    }  
} // contest_result_effect::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Adjust the components of the effect.
 * \param elapsed_time Elapsed time since the last call.
 */
bear::universe::time_type
ptb::contest_result_effect::progress( bear::universe::time_type elapsed_time )
{
  const bear::universe::time_type result( super::progress(elapsed_time) );

  if ( is_finished() )
    bear::engine::game::get_instance().set_waiting_level
      ("level/title_screen.cl");

  return result;
} // contest_result_effect::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Render the components of the effect.
 * \param e (out) The scene elements.
 */
void ptb::contest_result_effect::render( scene_element_list& e ) const
{
  super::render(e);
  
  bear::visual::position_type middle(get_layer().get_size() / 2);

  bear::visual::scene_sprite sp1
    ( middle.x - 50 - m_player_1.width(), 
      middle.y - m_player_1.height() / 2, m_player_1 );
  
  bear::visual::scene_sprite sp2
    (middle.x + 50, middle.y - m_player_2.height() / 2, m_player_2 );
 
  e.push_back( sp1 );
  e.push_back( sp2 );
} // contest_result_effect::render()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the world in which we search the bonus points.
 * \param w The world.
 */
void ptb::contest_result_effect::set_world( const bear::engine::world* w )
{
  m_world = w;
} // contest_result_effect::set_world()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the index of the loser.
 * \param index The index of the loser.
 */
void ptb::contest_result_effect::set_loser_index( unsigned int index )
{
  m_loser_index = index;
} // contest_result_effect::set_loser_index()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the effect that a key had been pressed.
 * \param key The value of the pressed key.
 * \remark This effect pretends to treat all keys, so we can maintain the pause
 *         mode.
 */
bool ptb::contest_result_effect::key_pressed( const bear::input::key_info& key )
{
  // prevent pausing the game
  return true;
} // contest_result_effect::key_pressed()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the effect that a joystick button had been pressed.
 * \param button The value of the pressed button.
 * \param joy_index The index of the joystick.
 * \remark This effect pretends to treat all keys, so we can maintain the pause
 *         mode.
 */
bool ptb::contest_result_effect::button_pressed
( bear::input::joystick::joy_code button, unsigned int joy_index )
{
  // prevent pausing the game
  return true;
} // contest_result_effect::button_pressed()

/*----------------------------------------------------------------------------*/
/**
 * \brief Update bonus states alive in the world.
 */
void ptb::contest_result_effect::update_bonus_state()
{
  if ( m_world == NULL )
    return;

  bear::engine::world::const_item_iterator it;

  for (it=m_world->living_items_begin(); it!=m_world->living_items_end(); ++it)
    {
      bonus_manager* manager =
        dynamic_cast<bonus_manager*>(&(*it));

      if ( manager != NULL )
        manager->manage(false);
    }
} // contest_result_effect::update_bonus_state()
