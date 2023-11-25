#include "BaseOpt.h"

AFC_HOPT CreateOptionProcessor()
{
    return new afc::optobj();
}

void DestroyOptionProcessor(AFC_HOPT hOpt)
{
    delete (afc::optobj*)hOpt;
}

void BindOption(AFC_HOPT hOpt, int argc, char* argv[])
{
    afc::optobj* hopt = (afc::optobj*)hOpt;
    hopt->bindopt(argc, argv);
}

int ProcOption(AFC_HOPT hOpt, AFC_RULE* RuleList)
{
    afc::optobj* hopt = (afc::optobj*)hOpt;
    return hopt->procopt(RuleList);
}

int GetOption(AFC_HOPT hOpt, char* buffer, int bufsize)
{
    afc::optobj* hopt = (afc::optobj*)hOpt;
    return hopt->getopt(buffer, bufsize);
}
