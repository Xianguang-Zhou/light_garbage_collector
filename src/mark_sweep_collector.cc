/*
 * Copyright (c) 2018, 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All
 * rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "mark_sweep_collector.h"

#include <forward_list>

namespace Lgc {

MarkSweepCollector::MarkSweepCollector(Context &context) : context(context) {}

void MarkSweepCollector::clean() {
	std::forward_list<void *> toScanObjects;

	// mark
	Objects *rootObjects = context.getRootObjects();
	for (void *object = rootObjects->nextObject(); nullptr != object;
		 object = rootObjects->nextObject()) {
		if (0 == context.getMark(object)) {
			context.setMark(object, 1);
			toScanObjects.push_front(object);
		}
	}
	delete rootObjects;

	while (!toScanObjects.empty()) {
		void *object = toScanObjects.front();
		toScanObjects.pop_front();

		Objects *properties = context.getProperties(object);
		for (void *property = properties->nextObject(); nullptr != property;
			 property = properties->nextObject()) {
			if (0 == context.getMark(property)) {
				context.setMark(property, 1);
				toScanObjects.push_front(property);
			}
		}
		delete properties;
	}

	// sweep
	Objects *allObjects = context.getAllObjects();
	for (void *object = allObjects->nextObject(); nullptr != object;
		 object = allObjects->nextObject()) {
		if (0 == context.getMark(object)) {
			toScanObjects.push_front(object);
			context.finalizeObject(object);
		} else {
			context.setMark(object, 0);
		}
	}
	delete allObjects;

	for (void *object : toScanObjects) {
		context.freeObject(object);
	}
}

} // namespace Lgc
