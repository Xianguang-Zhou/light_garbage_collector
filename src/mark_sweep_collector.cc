/*
 * Copyright (c) 2018, 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All
 * rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
