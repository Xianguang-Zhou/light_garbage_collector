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
