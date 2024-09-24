#ifndef _SIGNAL_HPP_
#define _SIGNAL_HPP_

#include <vector>

class Signal {
	double time_step;
	double frequency;
	double amplitude;
	std::vector<double> waveform;

	Signal (double _time_step, double _frequency = 0.0, double amplitude = 1.0);

	/** A first-order low-pass filter. */
	void apply_low_pass_filter (double cutoff_freq);
};

#endif /* _SIGNAL_HPP_ */

