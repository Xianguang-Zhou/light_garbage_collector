/*
 * Copyright (c) 2018, 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All
 * rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "incremental_mark_sweep_collector.h"

namespace Lgc {

IncrementalMarkSweepCollector::IncrementalMarkSweepCollector(Context &context)
	: context(context) {}

void IncrementalMarkSweepCollector::initialMark() {
	Objects *rootObjects = context.getRootObjects();
	for (void *object = rootObjects->nextObject(); nullptr != object;
		 object = rootObjects->nextObject()) {
		if (0 == context.getMark(object)) {
			context.setMark(object, 1);
			toScanObjects.push_front(object);
		}
	}
	delete rootObjects;
}

bool IncrementalMarkSweepCollector::incrementalMark() {
	if (toScanObjects.empty()) {
		this->allObjects = context.getAllObjects();

		return false;
	} else {
		void *object = toScanObjects.front();
		toScanObjects.pop_front();
		context.setMark(object, 2);

		Objects *properties = context.getProperties(object);
		for (void *property = properties->nextObject(); nullptr != property;
			 property = properties->nextObject()) {
			if (0 == context.getMark(property)) {
				context.setMark(property, 1);
				toScanObjects.push_front(property);
			}
		}
		delete properties;

		return true;
	}
}

void IncrementalMarkSweepCollector::writeBarrier(void *object, void *property) {
	if (2 == context.getMark(object) && 0 == context.getMark(property)) {
		context.setMark(property, 1);
		toScanObjects.push_front(property);
	}
}

bool IncrementalMarkSweepCollector::incrementalFinalize() {
	void *object = this->allObjects->nextObject();
	if (nullptr == object) {
		delete this->allObjects;

		return false;
	} else {
		char mark = context.getMark(object);
		if (0 == mark) {
			toScanObjects.push_front(object);
			context.finalizeObject(object);
		} else if (2 == mark) {
			context.setMark(object, 0);
		}

		return true;
	}
}

void IncrementalMarkSweepCollector::allocBarrier(void *object) {
	context.setMark(object, 1);
	toScanObjects.push_front(object);
}

bool IncrementalMarkSweepCollector::incrementalFree() {
	if (toScanObjects.empty()) {
		return false;
	} else {
		void *object = toScanObjects.front();
		toScanObjects.pop_front();

		char mark = context.getMark(object);
		if (0 == mark) {
			context.freeObject(object);
		} else {
			context.setMark(object, 0);
		}

		return true;
	}
}

} // namespace Lgc
