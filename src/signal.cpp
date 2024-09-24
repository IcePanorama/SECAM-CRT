#include "signal.hpp"

#include <cmath>
#include <cstddef>

Signal::Signal (double _time_step, double _frequency, double _amplitude)
    : time_step (_time_step), frequency (_frequency), amplitude (_amplitude)
{
}

void
Signal::apply_low_pass_filter (double cutoff_freq)
{
  std::vector<double> filtered_waveform (waveform.size (), 0.0);

  const double TIME_CONST = 1.0 / (cutoff_freq * 2 * M_PI);
  const double ALPHA = time_step / (TIME_CONST + time_step);

  filtered_waveform.at (0) = waveform.at (0);
  for (size_t i = 1; i < waveform.size (); i++)
    {
      filtered_waveform[i]
          = filtered_waveform[i - 1]
            + ALPHA * (waveform[i] - filtered_waveform[i - 1]);
    }

  waveform = filtered_waveform;
}
