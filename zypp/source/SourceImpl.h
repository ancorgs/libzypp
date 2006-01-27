/*---------------------------------------------------------------------\
|                          ____ _   __ __ ___                          |
|                         |__  / \ / / . \ . \                         |
|                           / / \ V /|  _/  _/                         |
|                          / /__ | | | | | |                           |
|                         /_____||_| |_| |_|                           |
|                                                                      |
\---------------------------------------------------------------------*/
/** \file	zypp/source/SourceImpl.h
 *
*/
#ifndef ZYPP_SOURCE_SOURCEIMPL_H
#define ZYPP_SOURCE_SOURCEIMPL_H

#include <iosfwd>

#include "zypp/base/ReferenceCounted.h"
#include "zypp/base/NonCopyable.h"
#include "zypp/base/PtrTypes.h"
#include "zypp/ResStore.h"

#include "zypp/Pathname.h"
#include "zypp/media/MediaAccess.h"
#include "zypp/Source.h"

///////////////////////////////////////////////////////////////////
namespace zypp
{ /////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////
  namespace source
  { /////////////////////////////////////////////////////////////////

    DEFINE_PTR_TYPE(SourceImpl);

    ///////////////////////////////////////////////////////////////////
    //
    //	CLASS NAME : SourceImpl
    //
    /** Base class for concrete Source implementations.
     *
     * Constructed by \ref SourceFactory. Public access via \ref Source
     * interface.
    */
    class SourceImpl : public base::ReferenceCounted, private base::NonCopyable
    {
      friend std::ostream & operator<<( std::ostream & str, const SourceImpl & obj );

    public:
      /** Ctor, FIXME it is here only because of target storage, then make it private */
      SourceImpl()
      : _res_store_initialized(true) // in case of null source, nothing to read
      {}
      /** Ctor. */
      SourceImpl(media::MediaAccess::Ptr & media_r,
                 const Pathname & path_r = "/");
      /** Dtor. */
      virtual ~SourceImpl();

      /** Null implementation */
      static SourceImpl_Ptr nullimpl();

    public:

      /** All resolvables provided by this source. */
      const ResStore & resolvables(Source & source_r);

      /** Provide a file to local filesystem */
      const Pathname provideFile(const Pathname & file,
				 const unsigned media_nr = 1);

      /** Provide a directory to local filesystem */
      const Pathname provideDir(const Pathname & path,
				const unsigned media_nr = 1,
				const bool recursive = false);

      const bool enabled() const
      { return _enabled; }

      void enable()
      { _enabled = true; }

      void disable()
      { _enabled = false; }

      /** Overload to realize stream output. */
      virtual std::ostream & dumpOn( std::ostream & str ) const
      { return str << "SourceImpl"; }

    protected:
      /** All resolvables provided by this source. */
      ResStore _store;
      /** Handle to media which contains this source */
      media::MediaAccess::Ptr _media;
      /** Path to the source on the media */
      Pathname _path;
      /** The source is enabled */
      bool _enabled;
    private:
      /** Null implementation */
      static SourceImpl_Ptr _nullimpl;
      /** ResStore initialized? */
      bool _res_store_initialized;
      /** Fill in the ResStore */
      virtual void createResolvables(Source & source_r);
    };
    ///////////////////////////////////////////////////////////////////

    /** \relates SourceImpl Stream output */
    inline std::ostream & operator<<( std::ostream & str, const SourceImpl & obj )
    { return obj.dumpOn( str ); }

    /////////////////////////////////////////////////////////////////
  } // namespace source
  ///////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////
} // namespace zypp
///////////////////////////////////////////////////////////////////
#endif // ZYPP_SOURCE_SOURCEIMPL_H
