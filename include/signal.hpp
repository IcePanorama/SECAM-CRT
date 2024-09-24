#ifndef _SIGNAL_HPP_
#define _SIGNAL_HPP_

#include <vector>

class Signal
{
  double time_step;
  double frequency;
  double amplitude;
  std::vector<double> waveform;

  Signal (double _time_step, double _frequency = 0.0, double amplitude = 1.0);

  /** A first-order low-pass filter. `cutoff_freq` is in Hertz. */
  void apply_low_pass_filter (double cutoff_freq);
  /**
   *  Modulates a signal with linear FM modulation. For chroma only.
   *  `carrier_frequency` is in Hertz.
   */
  void modulate_frequency (double chroma_value, double carrier_frequency,
                           size_t length);
  /** Modulates a signal. For Luma only. `carrier_frequency` is in Hertz. */
  void modulate_amplitude (double luma_value, size_t length);
};

#endif /* _SIGNAL_HPP_ */
