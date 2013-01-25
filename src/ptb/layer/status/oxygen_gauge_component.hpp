/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The component to display oxygen gauge.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_OXYGEN_GAUGE_COMPONENT_HPP__
#define __PTB_OXYGEN_GAUGE_COMPONENT_HPP__

#include "ptb/layer/status/gauge_component.hpp"

namespace ptb
{
  /**
   * \brief The component to display oxygen gauge.
   * \author Sebastien Angibaud
   */
  class oxygen_gauge_component :
    public gauge_component
  {
  public:
    /** \brief The type of the parent class. */
    typedef gauge_component super;

  public:
    oxygen_gauge_component
    ( bear::engine::level_globals& glob, const player_proxy& p, 
      const bear::visual::position_type& active_position,
      bear::universe::zone::position side,
      x_placement x_p, y_placement y_p,
      const bear::universe::size_box_type& layer_size);

  protected:
    void init_signals();

  private:
    void on_oxygen_gauge_changed(double level);
  }; // class oxygen_gauge_component
} // namespace ptb

#endif // __PTB_OXYGEN_GAUGE_COMPONENT_HPP__