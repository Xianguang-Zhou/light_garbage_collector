/*
 * Copyright (c) 2018, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <cstddef>
#include <list>
#include "mark_sweep_collector.hpp"

namespace Lgc {

MarkSweepCollector::MarkSweepCollector(Context& context) :
		context(context) {
}

void MarkSweepCollector::clean() {
	std::list<void *> toScanObjects;

	// mark
	Objects *globalObjects = context.getGlobalObjects();
	for (void *object = globalObjects->nextObject(); NULL != object; object =
			globalObjects->nextObject()) {
		if (0 == context.getMark(object)) {
			context.setMark(object, 1);
			toScanObjects.push_back(object);
		}
	}
	delete globalObjects;

	while (!toScanObjects.empty()) {
		void *object = toScanObjects.back();
		toScanObjects.pop_back();

		Objects *properties = context.getProperties(object);
		for (void *property = properties->nextObject(); NULL != property;
				property = properties->nextObject()) {
			if (0 == context.getMark(property)) {
				context.setMark(property, 1);
				toScanObjects.push_back(property);
			}
		}
		delete properties;
	}

	// sweep
	Objects *allObjects = context.getAllObjects();
	for (void *object = allObjects->nextObject(); NULL != object; object =
			allObjects->nextObject()) {
		if (0 == context.getMark(object)) {
			context.finalizeObject(object);
			toScanObjects.push_back(object);
		} else {
			context.setMark(object, 0);
		}
	}
	delete allObjects;

	for (std::list<void *>::const_iterator it = toScanObjects.begin();
			toScanObjects.end() != it; it++) {
		context.freeObject(*it);
	}
}
}

