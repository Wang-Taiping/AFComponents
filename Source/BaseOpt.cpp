#include "OptProc.h"

AFC_HOPT AFC_CreateOptionProcessor()
{
    return new afc::optobj();
}

void AFC_DestroyOptionProcessor(AFC_HOPT hOpt)
{
    delete (afc::optobj*)hOpt;
}

void AFC_BindOption(AFC_HOPT hOpt, int argc, char* argv[])
{
    afc::optobj* hopt = (afc::optobj*)hOpt;
    hopt->bindopt(argc, argv);
}

int AFC_ProcOption(AFC_HOPT hOpt, AFC_RULE* RuleList)
{
    afc::optobj* hopt = (afc::optobj*)hOpt;
    return hopt->procopt(RuleList);
}

int AFC_GetOption(AFC_HOPT hOpt, char* buffer, int bufsize)
{
    afc::optobj* hopt = (afc::optobj*)hOpt;
    return hopt->getopt(buffer, bufsize);
}
