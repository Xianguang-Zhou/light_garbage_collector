/*
 * Copyright (c) 2018, 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights
 * reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "mark_sweep_collector.h"

#include <cstddef>
#include <list>

namespace Lgc {

MarkSweepCollector::MarkSweepCollector(Context &context) : context(context) {}

void MarkSweepCollector::clean() {
	std::list<void *> toScanObjects;

	// mark
	Objects *rootObjects = context.getRootObjects();
	for (void *object = rootObjects->nextObject(); NULL != object;
		 object = rootObjects->nextObject()) {
		if (0 == context.getMark(object)) {
			context.setMark(object, 1);
			toScanObjects.push_back(object);
		}
	}
	delete rootObjects;

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
	for (void *object = allObjects->nextObject(); NULL != object;
		 object = allObjects->nextObject()) {
		if (0 == context.getMark(object)) {
			toScanObjects.push_back(object);
			context.finalizeObject(object);
		} else {
			context.setMark(object, 0);
		}
	}
	delete allObjects;

	for (std::list<void *>::const_iterator it = toScanObjects.begin();
		 toScanObjects.end() != it; ++it) {
		context.freeObject(*it);
	}
}

} // namespace Lgc
