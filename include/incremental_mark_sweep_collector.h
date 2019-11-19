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
#ifndef LGC_INCREMENTAL_MARK_SWEEP_COLLECTOR_H_
#define LGC_INCREMENTAL_MARK_SWEEP_COLLECTOR_H_

#include "context.h"

#include <forward_list>

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
	std::forward_list<void *> toScanObjects;
	Objects *allObjects;
};

} // namespace Lgc

#endif
