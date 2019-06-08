/*
 * Copyright (c) 2018, 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights
 * reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef LGC_MARK_SWEEP_COLLECTOR_H_
#define LGC_MARK_SWEEP_COLLECTOR_H_

#include "context.h"

namespace Lgc {

class MarkSweepCollector {
  public:
	explicit MarkSweepCollector(Context &context);
	void clean();

  private:
	Context &context;
};

} // namespace Lgc

#endif
