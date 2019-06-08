/*
 * Copyright (c) 2018, 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights
 * reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef LGC_INCREMENTAL_MARK_SWEEP_COLLECTOR_H_
#define LGC_INCREMENTAL_MARK_SWEEP_COLLECTOR_H_

#include <list>

#include "context.h"

namespace Lgc {

class IncrementalMarkSweepCollector {
  public:
	explicit IncrementalMarkSweepCollector(Context &context);

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
	Context &context;
	std::list<void *> toScanObjects;
	Objects *allObjects;
};

} // namespace Lgc

#endif
