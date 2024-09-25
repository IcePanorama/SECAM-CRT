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

  const double time_const = 1.0 / (cutoff_freq * 2 * M_PI);
  const double alpha = time_step / (time_const + time_step);

  filtered_waveform.at (0) = waveform.at (0);
  for (size_t i = 1; i < waveform.size (); i++)
    {
      filtered_waveform[i]
          = filtered_waveform[i - 1]
            + alpha * (waveform[i] - filtered_waveform[i - 1]);
    }

  waveform = filtered_waveform;
}

void
Signal::modulate_frequency (double chroma_value, double carrier_frequency,
                            size_t length)
{
  waveform.clear ();
  const double modulated_frequency = carrier_frequency + chroma_value;

  for (size_t i = 0; i < length; i++)
    {
      const double time = i * time_step;
      const double value
          = amplitude * std::sin (2 * M_PI * modulated_frequency * time);
      waveform.push_back (value);
    }
}

void
Signal::modulate_amplitude (double luma_value, size_t length)
{
  waveform.clear ();
  for (size_t i = 0; i < length; i++)
    {
      const double time = i * time_step;
      const double value
          = luma_value * amplitude * std::sin (2 * M_PI * frequency * time);
      waveform.push_back (value);
    }
}

void
Signal::combine (const Signal &s)
{
  // FIXME: should this throw a runtime error?
  if (waveform.size () != s.waveform.size ())
    return;

  for (size_t i = 0; i < waveform.size (); i++)
    waveform.at (i) += s.waveform.at (i);
}
