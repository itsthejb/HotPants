/*
 * ModuleCache.hpp
 *
 * Maintains a cache of Voice sub-modules; filters, amp and modulations.
 * Most of the time new notes will be generated without getParameters being
 * changed. If so, we can clone these saved modules and refresh them
 * when getParameters are actually changed.
 *
 *  Created on: 24 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef MODULECACHE_H_
#define MODULECACHE_H_

#include "../Interface/Interfaces.hpp"
#include "FilterModule.hpp"
#include "AmpModule.hpp"
#include "ModModule.hpp"

namespace hotpants {

  class ModuleCache: public Component
  {
    public:
      explicit              ModuleCache(HotPantsCore& c)
                            : Component(c),       cachedFilterModule(c),
                              cachedAmpModule(c), cachedModModule(c) {}
      // module access
      const FilterModule&   getFilterModule()                 { return cachedFilterModule; }
      const AmpModule&      getAmpModule()                    { return cachedAmpModule; }
      const ModModule&      getModModule()                    { return cachedModModule; }
      // module mutator
      void                  setFilterModule(FilterModule& x)  { cachedFilterModule = x; }
      void                  setAmpModule(AmpModule& x)        { cachedAmpModule = x; }
      void                  setModModule(ModModule& x)        { cachedModModule = x; }
    private:
      FilterModule          cachedFilterModule;
      AmpModule             cachedAmpModule;
      ModModule             cachedModModule;
  };

}
#endif /* MODULECACHE_H_ */
