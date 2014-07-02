/*************************************************************************
 *
 * This file is part of the SAMRAI distribution.  For full copyright
 * information, see COPYRIGHT and COPYING.LESSER.
 *
 * Copyright:     (c) 1997-2014 Lawrence Livermore National Security, LLC
 * Description:   A N-dimensional integer vector
 *
 ************************************************************************/

#ifndef included_hier_IntVector
#define included_hier_IntVector

#include "SAMRAI/SAMRAI_config.h"

#include "SAMRAI/tbox/Database.h"
#include "SAMRAI/tbox/Dimension.h"
#include "SAMRAI/tbox/MathUtilities.h"
#include "SAMRAI/tbox/Utilities.h"

#include <vector>
#include <iostream>

namespace SAMRAI {

namespace hier {

/**
 * Class IntVector implements a simple N-dimensional integer
 * vector.  This class is the base class for most of the simple indexing
 * classes.
 *
 */

class IntVector
{
public:
   typedef tbox::Dimension::dir_t dir_t;

   /**
    * @brief Creates an uninitialized vector.
    */
   explicit IntVector(
      const tbox::Dimension& dim);

   /**
    * @brief Construct an integer vector with all components equal to the
    *        argument.
    */
   IntVector(
      const tbox::Dimension& dim,
      const int i);

   /**
    * @brief Construct a n-dimensional integer vector with the value with
    *        values provided by the array.
    *
    * Dimension inferred from array size.
    */
   explicit IntVector(
      const std::vector<int>& a);

   /**
    * @brief Construct a n-dimensional integer vector with
    *        values provided by the array.
    *
    */
   IntVector(
      const tbox::Dimension& dim,
      const int array[]);

   /**
    * @brief Construct an integer vector equal to the argument.
    */
   IntVector(
      const IntVector& rhs);

   /**
    * @brief The assignment operator sets the integer vector equal to the
    *        argument.
    *
    * @pre getDim() == rhs.getDim()
    */
   IntVector&
   operator = (
      const IntVector& rhs)
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, rhs);
      for (int i = 0; i < getDim().getValue(); ++i) {
         d_vector[i] = rhs.d_vector[i];
      }
#ifdef DEBUG_INITIALIZE_UNDEFINED
      for (int i = getDim().getValue(); i < SAMRAI::MAX_DIM_VAL; ++i) {
         d_vector[i] = tbox::MathUtilities<int>::getMin();
      }
#endif
      return *this;
   }

   /**
    * @brief The integer vector destructor does nothing interesting.
    */
   virtual ~IntVector();

   /**
    * @brief Return the specified component of the vector.  No bounds checking.
    *
    * @pre (i >= 0) && (i < getDim().getValue())
    */
   int&
   operator [] (
      const int i)
   {
      TBOX_ASSERT(i >= 0 && i < getDim().getValue());
      return d_vector[i];
   }

   /**
    * @brief Return the specified component of the vector as a const integer.
    * No bounds checking.
    *
    * @pre (i >= 0) && (i < getDim().getValue())
    */
   const int&
   operator [] (
      const int i) const
   {
      TBOX_ASSERT(i >= 0 && i < getDim().getValue());
      return d_vector[i];
   }


   /**
    * @brief Return the specified component of the vector.  No bounds checking.
    *
    * @pre (i >= 0) && (i < getDim().getValue())
    */
   int&
   operator () (
      const int i)
   {
      TBOX_ASSERT(i >= 0 && i < getDim().getValue());
      return d_vector[i];
   }

   /**
    * @brief Return the specified component of the vector as a const integer.
    * No bounds checking.
    *
    * @pre (i >= 0) && (i < getDim().getValue())
    */
   const int&
   operator () (
      const int i) const
   {
      TBOX_ASSERT(i >= 0 && i < getDim().getValue());
      return d_vector[i];
   }

   /**
    * @brief Plus-equals operator for two integer vectors.
    *
    * @pre getDim() == rhs.getDim()
    */
   IntVector&
   operator += (
      const IntVector& rhs)
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, rhs);
      for (int i = 0; i < getDim().getValue(); ++i) {
         d_vector[i] += rhs.d_vector[i];
      }
      return *this;
   }

   /**
    * @brief Plus operator for two integer vectors.
    *
    * @pre getDim() == rhs.getDim()
    */
   IntVector
   operator + (
      const IntVector& rhs) const
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, rhs);
      IntVector tmp(*this);
      tmp += rhs;
      return tmp;
   }

   /**
    * @brief Plus-equals operator for an integer vector and an integer.
    */
   IntVector&
   operator += (
      const int rhs)
   {
      for (int i = 0; i < getDim().getValue(); ++i) {
         d_vector[i] += rhs;
      }
      return *this;
   }

   /**
    * @brief Plus operator for an integer vector and an integer.
    */
   IntVector
   operator + (
      const int rhs) const
   {
      IntVector tmp = *this;
      tmp += rhs;
      return tmp;
   }

   /**
    * @brief Minus-equals operator for two integer vectors.
    *
    * @pre getDim() == rhs.getDim()
    */
   IntVector&
   operator -= (
      const IntVector& rhs)
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, rhs);
      for (int i = 0; i < getDim().getValue(); ++i) {
         d_vector[i] -= rhs.d_vector[i];
      }
      return *this;
   }

   /**
    * @brief Minus operator for two integer vectors.
    *
    * @pre getDim() == rhs.getDim()
    */
   IntVector
   operator - (
      const IntVector& rhs) const
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, rhs);
      IntVector tmp = *this;
      tmp -= rhs;
      return tmp;
   }

   /**
    * @brief Minus-equals operator for an integer vector and an integer.
    */
   IntVector&
   operator -= (
      const int rhs)
   {
      for (int i = 0; i < getDim().getValue(); ++i) {
         d_vector[i] -= rhs;
      }
      return *this;
   }

   /**
    * @brief Minus operator for an integer vector and an integer.
    */
   IntVector
   operator - (
      const int rhs) const
   {
      IntVector tmp = *this;
      tmp -= rhs;
      return tmp;
   }

   /**
    * @brief Times-equals operator for two integer vectors.
    *
    * @pre getDim() == rhs.getDim()
    */
   IntVector&
   operator *= (
      const IntVector& rhs)
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, rhs);
      for (int i = 0; i < getDim().getValue(); ++i) {
         d_vector[i] *= rhs.d_vector[i];
      }
      return *this;
   }

   /**
    * @brief Times operator for two integer vectors.
    *
    * @pre getDim() == rhs.getDim()
    */
   IntVector
   operator * (
      const IntVector& rhs) const
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, rhs);
      IntVector tmp = *this;
      tmp *= rhs;
      return tmp;
   }

   /**
    * @brief Times-equals operator for an integer vector and an integer.
    */
   IntVector&
   operator *= (
      const int rhs)
   {
      for (int i = 0; i < getDim().getValue(); ++i) {
         d_vector[i] *= rhs;
      }
      return *this;
   }

   /**
    * @brief Times operator for an integer vector and an integer.
    */
   IntVector
   operator * (
      const int rhs) const
   {
      IntVector tmp = *this;
      tmp *= rhs;
      return tmp;
   }

   /**
    * @brief Assign-quotient operator for two integer vectors.
    *
    * @pre getDim() == rhs.getDim()
    */
   IntVector&
   operator /= (
      const IntVector& rhs)
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, rhs);
      for (int i = 0; i < getDim().getValue(); ++i) {
         d_vector[i] /= rhs.d_vector[i];
      }
      return *this;
   }

   /**
    * @brief Component-wise ceilingDivide quotient (integer divide with
    *        rounding up).
    *
    * @pre getDim() == denominator.getDim()
    */
   void
   ceilingDivide(
      const IntVector& denominator)
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, denominator);
      for (int i = 0; i < getDim().getValue(); ++i) {
         /*
          * This is the formula for integer divide, rounding away from
          * zero.  It is meant as an extension of the ceilingDivide quotient of
          * 2 positive integers.
          *
          * The ceilingDivide is the integer divide plus 0, -1 or 1 representing
          * the results of rounding.
          * - Add zero if there's no remainder to round.
          * - Round remainder to 1 if numerator and denominator has same sign.
          * - Round remainder to -1 if numerator and denominator has opposite sign.
          */
         d_vector[i] = (d_vector[i] / denominator[i]) +
            ((d_vector[i] % denominator[i]) ?
               ((d_vector[i] > 0) == (denominator[i] > 0) ? 1 : -1) : 0);
      }
   }

   /**
    * @brief Component-wise ceilingDivide quotient (integer divide with
    *        rounding up).
    *
    * @pre numerator.getDim() == denominator.getDim()
    */
   static IntVector
   ceilingDivide(
      const IntVector& numerator,
      const IntVector& denominator)
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(numerator, denominator);
      IntVector rval(numerator.getDim());
      for (int i = 0; i < numerator.getDim().getValue(); ++i) {
         /*
          * This is the formula for integer divide, rounding away from
          * zero.  It is meant as an extension of the ceilingDivide quotient of
          * 2 positive integers.
          *
          * The ceilingDivide is the integer divide plus 0, -1 or 1 representing
          * the results of rounding.
          * - Add zero if there's no remainder to round.
          * - Round remainder to 1 if numerator and denominator has same sign.
          * - Round remainder to -1 if numerator and denominator has opposite sign.
          */
         rval[i] = (numerator[i] / denominator[i]) +
            ((numerator[i] % denominator[i]) ?
               ((numerator[i] > 0) == (denominator[i] > 0) ? 1 : -1) : 0);
      }
      return rval;
   }

   /**
    * @brief Quotient operator for two integer vectors.
    *
    * @pre getDim() == rhs.getDim()
    */
   IntVector
   operator / (
      const IntVector& rhs) const
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, rhs);
      IntVector tmp = *this;
      tmp /= rhs;
      return tmp;
   }

   /**
    * @brief Assign-quotient operator for an integer vector and an integer.
    */
   IntVector&
   operator /= (
      const int rhs)
   {
      for (int i = 0; i < getDim().getValue(); ++i) {
         d_vector[i] /= rhs;
      }
      return *this;
   }

   /**
    * @brief Quotient operator for an integer vector and an integer.
    */
   IntVector
   operator / (
      const int rhs) const
   {
      IntVector tmp = *this;
      tmp /= rhs;
      return tmp;
   }

   /**
    * @brief Unary minus to negate an integer vector.
    */
   IntVector
   operator - () const
   {
      IntVector tmp(getDim());
      for (int i = 0; i < getDim().getValue(); ++i) {
         tmp.d_vector[i] = -d_vector[i];
      }
      return tmp;
   }

   /**
    * @brief Returns true if all components are equal to a given integer.
    */
   bool
   operator == (
      int rhs) const
   {
      bool result = true;
      for (int i = 0; result && (i < getDim().getValue()); ++i) {
         result = d_vector[i] == rhs;
      }
      return result;
   }

   /**
    * @brief Returns true if some components are not equal to a given integer.
    */
   bool
   operator != (
      int rhs) const
   {
      bool result = true;
      for (int i = 0; result && (i < getDim().getValue()); ++i) {
         result = d_vector[i] != rhs;
      }
      return result;
   }

   /**
    * @brief Returns true if two vector objects are equal.  All components
    *        must be the same for equality.
    *
    * @pre getDim() == rhs.getDim()
    */
   bool
   operator == (
      const IntVector& rhs) const
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, rhs);
      bool result = true;
      for (int i = 0; result && (i < getDim().getValue()); ++i) {
         result = result && (d_vector[i] == rhs.d_vector[i]);
      }
      return result;
   }

   /**
    * @brief Returns true if two vector objects are not equal.  Any of
    *        the components may be different for inequality.
    *
    * @pre getDim() == rhs.getDim()
    */
   bool
   operator != (
      const IntVector& rhs) const
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, rhs);
      return !(*this == rhs);
   }

   /**
    * @brief Returns true if each integer in vector is less than
    *        corresponding integer in comparison vector.
    *
    * @pre getDim() == rhs.getDim()
    */
   bool
   operator < (
      const IntVector& rhs) const
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, rhs);
      bool result = true;
      for (int i = 0; result && (i < getDim().getValue()); ++i) {
         result = result && (d_vector[i] < rhs.d_vector[i]);
      }
      return result;
   }

   /**
    * @brief Returns true if each integer in vector is less or equal to
    *        corresponding integer in comparison vector.
    *
    * @pre getDim() == rhs.getDim()
    */
   bool
   operator <= (
      const IntVector& rhs) const
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, rhs);
      bool result = true;
      for (int i = 0; result && (i < getDim().getValue()); ++i) {
         result = result && (d_vector[i] <= rhs.d_vector[i]);
      }
      return result;
   }

   /**
    * @brief Returns true if each integer in vector is greater than
    *        corresponding integer in comparison vector.
    *
    * @pre getDim() == rhs.getDim()
    */
   bool
   operator > (
      const IntVector& rhs) const
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, rhs);
      bool result = true;
      for (int i = 0; result && (i < getDim().getValue()); ++i) {
         result = result && (d_vector[i] > rhs.d_vector[i]);
      }
      return result;
   }

   /**
    * @brief Returns true if each integer in vector is greater or equal to
    *        corresponding integer in comparison vector.
    *
    * @pre getDim() == rhs.getDim()
    */
   bool
   operator >= (
      const IntVector& rhs) const
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, rhs);
      bool result = true;
      for (int i = 0; result && (i < getDim().getValue()); ++i) {
         result = result && (d_vector[i] >= rhs.d_vector[i]);
      }
      return result;
   }

   /**
    * @brief Return the component-wise minimum of two integer vector objects.
    *
    * @pre getDim() == rhs.getDim()
    */
   void
   min(
      const IntVector& rhs)
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, rhs);
      for (int i = 0; i < getDim().getValue(); ++i) {
         if (rhs.d_vector[i] < d_vector[i]) {
            d_vector[i] = rhs.d_vector[i];
         }
      }
   }

   /**
    * @brief Return the minimum entry in an integer vector.
    */
   int
   min() const
   {
      int min = d_vector[0];
      for (int i = 1; i < getDim().getValue(); ++i) {
         if (d_vector[i] < min) {
            min = d_vector[i];
         }
      }
      return min;
   }

   /**
    * @brief Return the component-wise maximum of two integer vector objects.
    */
   void
   max(
      const IntVector& rhs)
   {
      for (int i = 0; i < getDim().getValue(); ++i) {
         if (rhs.d_vector[i] > d_vector[i]) {
            d_vector[i] = rhs.d_vector[i];
         }
      }
   }

   /**
    * @brief Return the maximum entry in an integer vector.
    */
   int
   max() const
   {
      int max = d_vector[0];
      for (int i = 1; i < getDim().getValue(); ++i) {
         if (d_vector[i] > max) {
            max = d_vector[i];
         }
      }
      return max;
   }

   /**
    * @brief Utility function to take the minimum of two integer vector
    *        objects.
    *
    * @pre a.getDim() == b.getDim()
    */
   static IntVector
   min(
      const IntVector& a,
      const IntVector& b)
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(a, b);
      IntVector tmp = a;
      tmp.min(b);
      return tmp;
   }

   /**
    * @brief Utility function to take the maximum of two integer vector
    *        objects.
    *
    * @pre a.getDim() == b.getDim()
    */
   static IntVector
   max(
      const IntVector& a,
      const IntVector& b)
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(a, b);
      IntVector tmp = a;
      tmp.max(b);
      return tmp;
   }

   /**
    * @brief Return the product of the entries in the integer vector.
    */
   long int
   getProduct() const
   {
      long int prod = 1;
      for (int i = 0; i < getDim().getValue(); ++i) {
         prod *= d_vector[i];
      }
      return prod;
   }

   /**
    * @brief Store the object state to the specified restart database
    *        with the provided name.
    *
    */
   virtual void
   putToRestart(
      tbox::Database& restart_db,
      const std::string& name) const;

   /**
    * @brief Restores the object giving it the provided name and getting its
    *        state from the specified restart database.
    *
    */
   virtual void
   getFromRestart(
      tbox::Database& restart_db,
      const std::string& name);

   /**
    * @brief Return the dimension of this object.
    */
   const tbox::Dimension&
   getDim() const
   {
      return d_dim;
   }

   /*!
    * @brief Return an IntVector of zeros of the specified dimension.
    *
    * Can be used to avoid object creation overheads.
    */
   static const IntVector&
   getZero(
      const tbox::Dimension& dim)
   {
      return *(s_zeros[dim.getValue() - 1]);
   }

   /*!
    * @brief Return an IntVector of ones of the specified dimension.
    *
    * Can be used to avoid object creation overheads.
    */
   static const IntVector&
   getOne(
      const tbox::Dimension& dim)
   {
      return *(s_ones[dim.getValue() - 1]);
   }

   /*
    * @brief Sort the given IntVector the smallest to the largest value.
    *
    * Set the ith entry of this to the position of the ith smallest
    * value in the given IntVector.
    */
   void
   sortIntVector(
      const IntVector& values);

   /**
    * @brief Read an integer vector from an input stream.  The format for
    *        the input is (i0,...,in) for an n-dimensional vector.
    */
   friend std::istream&
   operator >> (
      std::istream& s,
      IntVector& rhs);

   /**
    * @brief Write an integer vector into an output stream.  The format for
    *        the output is (i0,...,in) for an n-dimensional vector.
    */
   friend std::ostream&
   operator << (
      std::ostream& s,
      const IntVector& rhs);

private:
   /*
    * Unimplemented default constructor
    */
   IntVector();

   /*!
    * @brief Initialize static objects and register shutdown routine.
    *
    * Only called by StartupShutdownManager.
    *
    */
   static void
   initializeCallback();

   /*!
    * @brief Method registered with ShutdownRegister to cleanup statics.
    *
    * Only called by StartupShutdownManager.
    */
   static void
   finalizeCallback();

   tbox::Dimension d_dim;

   int d_vector[SAMRAI::MAX_DIM_VAL];

   static IntVector* s_zeros[SAMRAI::MAX_DIM_VAL];
   static IntVector* s_ones[SAMRAI::MAX_DIM_VAL];

   static tbox::StartupShutdownManager::Handler
      s_initialize_finalize_handler;

};

}
}

#endif
