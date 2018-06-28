/*
 * Copyright (c) 2018, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights reserved.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef LGC_MARK_SWEEP_COLLECTOR_HPP
#define LGC_MARK_SWEEP_COLLECTOR_HPP

namespace Lgc {

class MarkSweepCollector {
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
		virtual Objects *getGlobalObjects()=0;
		virtual void setMark(void *object, char value)=0;
		virtual char getMark(void *object)=0;
	};

	explicit MarkSweepCollector(Context& context);
	void clean();

private:
	Context& context;
};
}

#endif

