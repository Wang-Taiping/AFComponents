#pragma once

#ifndef BASEOPT_H
#define BASEOPT_H

#include "BaseLibrary.h"
#include "OptProc.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	AFC_HOPT CreateOptionProcessor();
	void DestroyOptionProcessor(AFC_HOPT hOpt);
	void BindOption(AFC_HOPT hOpt, int argc, char* argv[]);
	int ProcOption(AFC_HOPT hOpt, AFC_RULE* RuleList);
	int GetOption(AFC_HOPT hOpt, char* buffer, int bufsize); // bool

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !BASEOPT_H
