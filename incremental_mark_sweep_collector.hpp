/*
 * Copyright (c) 2018, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef LGC_INCREMENTAL_MARK_SWEEP_COLLECTOR_HPP
#define LGC_INCREMENTAL_MARK_SWEEP_COLLECTOR_HPP

#include <list>

namespace Lgc {

class IncrementalMarkSweepCollector {
public:

	class Objects {
	public:
		virtual void *nextObject()=0;
		virtual ~Objects() {
		}
	};

	class Context {
	public:
		virtual void finalizeObject(void *object) {
		}
		virtual void freeObject(void *object)=0;
		virtual Objects *getProperties(void *object)=0;
		virtual Objects *getAllObjects()=0;
		virtual Objects *getRootObjects()=0;
		virtual void setMark(void *object, char value)=0;
		virtual char getMark(void *object)=0;
	};

	explicit IncrementalMarkSweepCollector(Context& context);

	// Garbage collection steps begin.

	/**
	 * The first step.
	 */
	void initialMark();
	/**
	 * The second step: call it until it returns "false".
	 */
	bool incrementalMark();
	/**
	 * In the second step, it is called after "object.field = property".
	 */
	void writeBarrier(void *object, void *property);
	/**
	 * The third step: call it until it returns "false".
	 */
	bool incrementalFinalize();
	/**
	 * In the third step, it is called after object allocation.
	 */
	void allocBarrier(void *object);
	/**
	 * The fourth step: call it until it returns "false".
	 */
	bool incrementalFree();

	// Garbage collection steps end.

private:
	Context& context;
	std::list<void *> toScanObjects;
	Objects *allObjects;
};
}

#endif

