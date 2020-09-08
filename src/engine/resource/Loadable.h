//
// Created by Stephen Welch on 9/2/2020.
//

#pragma once

#include <vector>

class Loadable {
 public:
	virtual ~Loadable() = default;
	void initializeAll() {
		init();
		for(auto &dependent : dependents) {
			dependent->initializeAll();
		}
	};
	virtual void init() {};
	auto getDependent() const { return dependents; }
	auto addDependent(Loadable *dependent) { dependents.push_back(dependent); }
 private:
	std::vector<Loadable*> dependents;
};