/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::ray class.
 * \author Sébastien Angibaud
 */
#include "ptb/item/player/ray.hpp"

BASE_ITEM_EXPORT( ray, ptb )

/*----------------------------------------------------------------------------*/
const bear::universe::coordinate_type ptb::ray::s_vertical_jump_force = 5000000;

const double ptb::ray::s_mass = 80;
const double ptb::ray::s_density = 1.5;

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::ray::ray()
  : super( get_physics() ), m_cry(false)
{
  set_mass(s_mass);
  set_density(s_density);
  set_size( 50, 110 );
} // ray::ray()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destructor.
 */
ptb::ray::~ray()
{
} // ray::~ray()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
void ptb::ray::pre_cache()
{
  super::pre_cache();

  // ray
  get_level_globals().load_model("model/player/ray.cm");

  // halo for soul
  get_level_globals().load_image("gfx/plee/misc.png");
} // ray::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do post creation actions.
 */
void ptb::ray::on_enters_layer()
{
  super::on_enters_layer();

  set_model_actor( get_level_globals().get_model("model/player/ray.cm") );
  start_action_model("idle");
  m_wait_state_number = 0;

  set_persistent_balloon( true );
} // ray::on_enters_layer()

/*---------------------------------------------------------------------------*/
/**
 * \brief Indicate that Ray starts to cry.
 */
void ptb::ray::start_cry()
{
  m_cry = true;

  update_cry_action();
} // ray::start_cry()

/*---------------------------------------------------------------------------*/
/**
 * \brief Indicate that Ray stops to cry.
 */
void ptb::ray::stop_cry()
{
  m_cry = false;

  update_cry_action();
} // ray::stop_cry()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "bool".
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::ray::set_bool_field
( const std::string& name, bool value )
{
  bool result = true;

  if (name == "ray.is_crying")
    {
      m_cry = value;
      update_cry_action();
    }
  else
    result = super::set_bool_field(name, value);

  return result;
} // ray::set_bool_field()

/*---------------------------------------------------------------------------*/
/**
 * \brief Choose a wait state.
 */
void ptb::ray::choose_wait_state()
{
  if ( !m_cry )
    super::choose_wait_state();
} // ray::choose_wait_state()

/*---------------------------------------------------------------------------*/
/**
 * \brief Choose an idle state.
 */
void ptb::ray::choose_idle_state()
{
  if ( m_cry )
    start_action_model("cry");
  else
    super::choose_idle_state();
} // ray::choose_idle_state()

/*---------------------------------------------------------------------------*/
/**
 * \brief Choose a walk state.
 */
void ptb::ray::choose_walk_state()
{
  if ( m_cry )
    start_action_model("walk-cry");
  else
    super::choose_walk_state();
} // ray::choose_walk_state()

/*---------------------------------------------------------------------------*/
/**
 * \brief Get the impulse force for vertical jumps.
 */
bear::universe::coordinate_type
ptb::ray::get_vertical_jump_force() const
{
  return s_vertical_jump_force;
} // ray::get_vertical_jump_force()

/*----------------------------------------------------------------------------*/
/**
 * \brief Give a string representation of the item.
 * \param str (out) The result of the convertion.
 */
void ptb::ray::to_string( std::string& str ) const
{
  std::ostringstream oss;

  super::to_string(str);

  oss << "cry: ";
  if (m_cry )
    oss << "true";
  else
    oss << "false";

  oss << "\n";

  str += oss.str();
} // player::to_string()

/*---------------------------------------------------------------------------*/
/**
 * \brief Get the sprite of the soul.
 */
bear::visual::sprite ptb::ray::get_soul_sprite() const
{
  return bear::visual::sprite
    ( get_level_globals().auto_sprite("gfx/plee/misc.png", "soul effet"));
} // ray::get_soul_sprite()

/*---------------------------------------------------------------------------*/
/**
 * \brief Update action when Ray changes its cry status.
 */
void ptb::ray::update_cry_action()
{
  if ( ( m_current_state == player::idle_state ) ||
       ( m_current_state == player::wait_state ) )
    choose_idle_state();
  else if ( m_current_state == player::walk_state )
    choose_walk_state();
} // ray::update_cry_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Gets the physics constants defining the behavior of this player.
 */
ptb::player_physics ptb::ray::get_physics() const
{
  player_physics result;

  result.move_force_in_jump = 64000;
  result.move_force_in_vertical_jump = 32000;
  result.move_force_in_run = 81000;
  result.move_force_in_swimming = 64000;
  result.move_force_in_walk = 24000;
  result.jump_force = 3000000;
  result.jump_force_in_float = 9200000;
  result.speed_to_run = 1000;
  
  return result;
} // ray::get_physics()

/*----------------------------------------------------------------------------*/
/**
 * \brief Export the methods of the class.
 */
void ptb::ray::init_exported_methods()
{
  TEXT_INTERFACE_CONNECT_METHOD_0
    ( ptb::ray, start_cry, void );
  TEXT_INTERFACE_CONNECT_METHOD_0
    ( ptb::ray, stop_cry, void );
} // ray::init_exported_methods()

/*----------------------------------------------------------------------------*/
TEXT_INTERFACE_IMPLEMENT_METHOD_LIST( ptb::ray )
