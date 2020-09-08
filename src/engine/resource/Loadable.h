//
// Created by Stephen Welch on 9/2/2020.
//

#pragma once

#include <vector>

class Loadable {
 public:
	virtual ~Loadable() = default;
	virtual void init() {
		LOG_WARN("WARNING: Loadable initializer is unimplemented");
	};
};