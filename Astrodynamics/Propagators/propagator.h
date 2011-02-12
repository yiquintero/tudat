/*! \file propagator.h
 *    Header file that defines the base class for all propagators included in
 *    Tudat.
 *
 *    Path              : /Astrodynamics/Propagators/
 *    Version           : 7
 *    Check status      : Checked
 *
 *    Author            : K. Kumar
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : K.Kumar@tudelft.nl
 *
 *    Checker           : J.C.P. Melman
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : J.C.P.Melman@tudelft.nl
 *
 *    Date created      : 14 September, 2010
 *    Last modified     : 7 February, 2011
 *
 *    References
 *
 *    Notes
 *
 *    Copyright (c) 2010 Delft University of Technology.
 *
 *    This software is protected by national and international copyright.
 *    Any unauthorized use, reproduction or modification is unlawful and
 *    will be prosecuted. Commercial and non-private application of the
 *    software in any form is strictly prohibited unless otherwise granted
 *    by the authors.
 *
 *    The code is provided without any warranty; without even the implied
 *    warranty of merchantibility or fitness for a particular purpose.
 *
 *    Changelog
 *      YYMMDD    Author              Comment
 *      100914    K. Kumar            File created.
 *      100926    K. Kumar            Added Doxygen comments.
 *      100928    K. Kumar            Completed missing comments.
 *      100929    J. Melman           Reference to Integrator::
 *                                    setFixedOutputInterval deleted,
 *                                    'class' in comments changed into 'object'.
 *      100929    K. Kumar            EigenRoutines.h replaced in include
 *                                    statements by linearAlgebra.h.
 *      110201    K. Kumar            Updated code to make use of State class;
 *                                    moved computeSumOfStateDerivatives_() to
 *                                    NumericalPropagator class.
 *      110207    K. Kumar            Added ostream overload.
 */

#ifndef PROPAGATOR_H
#define PROPAGATOR_H

// Include statements.
#include <iostream>
#include <map>
#include <vector>
#include "forceModel.h"
#include "propagatorDataContainer.h"
#include "body.h"
#include "linearAlgebra.h"
#include "state.h"

// Forward declarations.
class PropagatorDataContainer;

//! Propagator class.
/*!
 * Base class for all propagators included in Tudat.
 */
class Propagator
{
public:

    //! Default constructor.
    /*!
     * Default constructor.
     */
    Propagator( );

    //! Default destructor.
    /*!
     * Default destructor.
     */
    virtual ~Propagator( );

    //! Set start of propagation interval.
    /*!
     * Sets the start of the propagation interval.
     * \param propagationIntervalStart Start of propagation interval.
     */
    void setPropagationIntervalStart( const double& propagationIntervalStart );

    //! Set end of propagation interval.
    /*!
     * Sets the end of the propagation interval.
     * \param propagationIntervalEnd End of propagation interval.
     */
    void setPropagationIntervalEnd( const double& propagationIntervalEnd );

    //! Add body to be propagated.
    /*!
     * Adds a body to be propagated.
     * \param pointerToBody Pointer to Body object.
     */
    void addBody( Body* pointerToBody );

    //! Set propagator for propagation of a body.
    /*!
     * Sets a propagator for propagation of given body.
     * \param pointerToBody Pointer to Body object.
     * \param pointerToPropagator Pointer to Propagator object.
     */
    void setPropagator( Body* pointerToBody, Propagator* pointerToPropagator );

    //! Set initial state of body.
    /*!
     * Sets the initial state of given body.
     * \param pointerToBody Pointer to Body object.
     * \param initialState Initial state given as pointer to a State object.
     */
    void setInitialState( Body* pointerToBody, State* pointerToInitialState );

    //! Set fixed output interval.
    /*!
     * Sets the fixed output interval at which propagation output should be
     * generated and stored in propagationHistory_. Calls to this function are
     * optional.
     * \param fixedOutputInterval Fixed output interval.
     */
    void setFixedOutputInterval( const double& fixedOutputInterval );

    //! Get start of propagation interval.
    /*!
     * Gets the start of the propagation interval.
     * \return Start of propagation interval.
     */
    double& getPropagationIntervalStart( );

    //! Get end of propagation interval.
    /*!
     * Gets the end of the propagation interval.
     * \return End of propagation interval.
     */
    double& getPropagationIntervalEnd( );

    //! Get final state of body.
    /*!
     * Returns the final state of given body.
     * \param pointerToBody Pointer to Body object.
     * \return Final state.
     */
    State* getFinalState( Body* pointerToBody );

    //! Get propagation history of body at fixed output intervals.
    /*!
     * Returns the propagation history of given body at specified fixed output
     * intervals.
     * \param pointerToBody Pointer to Body object.
     * \return Map of propagation history.
     */
    std::map < double, State* >
            getPropagationHistoryAtFixedOutputIntervals( Body* pointerToBody );

    //! Propagate.
    /*!
     * This function executes propagation.
     */
    virtual void propagate( ) = 0;

    //! Overload ostream to print class information.
    /*!
     * Overloads ostream to print class information.
     * \param stream Stream object.
     * \param pointerToPropagator Pointer to Propagator.
     * \return Stream object.
     */
    friend std::ostream& operator<<( std::ostream& stream,
                                     Propagator* pointerToPropagator );

protected:

    //! Set start of propagation interval.
    /*!
     * Set start of propagation interval.
     */
    double propagationIntervalStart_;

    //! Set end of propagation interval.
    /*!
     * Set end of propagation interval.
     */
    double propagationIntervalEnd_;

    //! Fixed output interval.
    /*!
     * Fixed interval for output of state.
     */
    double fixedOutputInterval_;

    //! Map of bodies to propagate and associated data.
    /*!
     * Map of bodies to be propagated and associated data.
     */
    std::map < Body*, PropagatorDataContainer* > bodiesToPropagate_;

    //! Iterator for map of bodies to propagate and associated data.
    /*!
     * Iterator for map of bodies to propagate and associated data.
     */
    std::map < Body*, PropagatorDataContainer* >::iterator
            iteratorBodiesToPropagate_;

    //! Map of propagation history.
    /*!
     * Map of propagation history.
     */
    std::map < double, State* > propagationHistory_;

    //! Iterator for map of propagation history.
    /*!
     * Iterator for map of propagation history.
     */
    std::map < double, State* >::iterator iteratorPropagationHistory_;

private:
};

#endif // PROPAGATOR_H

// End of file.