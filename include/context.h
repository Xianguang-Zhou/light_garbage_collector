/*
 * Copyright (c) 2018, 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights
 * reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef LGC_CONTEXT_H_
#define LGC_CONTEXT_H_

namespace Lgc {

class Objects {
  public:
	virtual void *nextObject() = 0;
	virtual ~Objects() {}
};

class Context {
  public:
	virtual void finalizeObject(void *object) {}
	virtual void freeObject(void *object) = 0;
	virtual Objects *getProperties(void *object) = 0;
	virtual Objects *getAllObjects() = 0;
	virtual Objects *getRootObjects() = 0;
	virtual void setMark(void *object, char value) = 0;
	virtual char getMark(void *object) = 0;
	virtual ~Context() {}
};

} // namespace Lgc

#endif
