/*
 Copyright 2010 Microsoft Corp
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/

#ifndef watoolkitios_samples_Macros_h
#define watoolkitios_samples_Macros_h

/*
 LOG -- calls NSLog only if DEBUG is defined
 */
#ifdef DEBUG
#define LOG(...) NSLog(__VA_ARGS__)
#else
#define LOG(...) /* */
#endif

/*
 LOGLINE -- calls NSLog only if DEBUG is defined, also adds in file, line numbers
 */
#ifdef DEBUG
#define LOGLINE(fmt, ...) NSLog((@"%s [Line %d] " fmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);
#define FTLOGCALL LOG(@"[%@ %@]", NSStringFromClass([self class]), NSStringFromSelector(_cmd))
#else
#define LOGLINE(...) /* */
#define FTLOGCALL /* */
#endif

#if DEBUG 
#define RELEASE(_obj) [_obj release] 
#else 
#define RELEASE(_obj) [_obj release], _obj = nil 
#endif

#endif
