//
// File:	$URL: file:///usr/casc/samrai/repository/SAMRAI/tags/v-2-2-0/source/patchdata/boxgeometry/NodeGeometry.h $
// Package:	SAMRAI patch data geometry
// Copyright:	(c) 1997-2007 Lawrence Livermore National Security, LLC
// Revision:	$LastChangedRevision: 1704 $
// Modified:	$LastChangedDate: 2007-11-13 16:32:40 -0800 (Tue, 13 Nov 2007) $
// Description:	hier::Box geometry information for node centered objects
//

#ifndef included_pdat_NodeGeometry
#define included_pdat_NodeGeometry

#ifndef included_SAMRAI_config
#include "SAMRAI_config.h"
#endif
#ifndef included_hier_Box
#include "Box.h"
#endif
#ifndef included_hier_BoxGeometry
#include "BoxGeometry.h"
#endif
#ifndef included_hier_BoxOverlap
#include "BoxOverlap.h"
#endif
#ifndef included_hier_IntVector
#include "IntVector.h"
#endif
#ifndef included_tbox_Pointer
#include "tbox/Pointer.h"
#endif

namespace SAMRAI {
    namespace pdat {

/*!
 * Class NodeGeometry<DIM> manages the mapping between the AMR index space
 * and the node-centered geometry index space.  It is a subclass of
 * hier::BoxGeometry<DIM> and it computes intersections between node-
 * centered box geometries for communication operations.
 *
 * See header file for NodeData<DIM> class for a more detailed
 * description of the data layout.
 *
 * @see hier::BoxGeometry
 * @see pdat::NodeOverlap
 */

template<int DIM> class NodeGeometry : public hier::BoxGeometry<DIM>
{
public:
   /*!
    * @brief Convert an AMR index box space box into a node geometry box.
    * A node geometry box is extends the given AMR index box space box
    * by one in upper dimension for each coordinate direction.
    */
   static hier::Box<DIM> toNodeBox(const hier::Box<DIM>& box);

   /*!
    * @brief Construct the node geometry object given an AMR index
    * space box and ghost cell width. 
    */
   NodeGeometry(const hier::Box<DIM>& box, 
                const hier::IntVector<DIM>& ghosts);

   /*!
    * @brief The virtual destructor does nothing interesting.
    */
   virtual ~NodeGeometry<DIM>();

   /*!
    * @brief Compute the overlap in node-centered index space between
    * the source box geometry and the destination box geometry.
    */
   virtual tbox::Pointer< hier::BoxOverlap<DIM> > calculateOverlap(
      const hier::BoxGeometry<DIM>& dst_geometry,
      const hier::BoxGeometry<DIM>& src_geometry,
      const hier::Box<DIM>& src_mask,
      const bool overwrite_interior,
      const hier::IntVector<DIM>& src_offset,
      const bool retry) const;

   /*!
    * @brief Return the box for this node centered box geometry
    * object.
    */
   const hier::Box<DIM>& getBox() const;
 
   /*!
    * @brief Return the ghost cell width for this node centered box
    * geometry object.
    */
   const hier::IntVector<DIM>& getGhosts() const;

private:
   /**
    * Function doOverlap() is the function that computes the overlap
    * between the source and destination objects, where both box geometry
    * objects are guaranteed to have node centered geometry.
    */
   static tbox::Pointer< hier::BoxOverlap<DIM> > doOverlap(
      const NodeGeometry<DIM>& dst_geometry,
      const NodeGeometry<DIM>& src_geometry,
      const hier::Box<DIM>& src_mask,
      const bool overwrite_interior,
      const hier::IntVector<DIM>& src_offset);

   NodeGeometry(const NodeGeometry<DIM>&);	// not implemented
   void operator=(const NodeGeometry<DIM>&);		// not implemented

   hier::Box<DIM> d_box;
   hier::IntVector<DIM> d_ghosts;

};

}
}
#ifndef DEBUG_NO_INLINE
#include "NodeGeometry.I"
#endif
#endif

#ifdef INCLUDE_TEMPLATE_IMPLEMENTATION
#include "NodeGeometry.C"
#endif