#ifndef __BinaryStar_h__
#define __BinaryStar_h__

#include "constants.h"
#include "typedefs.h"

#include "BaseBinaryStar.h"


class BaseBinaryStar;

class BinaryStar {

public:


    /* Constructors
     *
     * Parameter p_Seed is the seed for the random number generator - see main.cpp for an
     * explanation of how p_Seed is derived.
     * 
     * Parameter p_Id is the id of the binary - effectively an index - which is added as
     * a suffix to the filenames of any detailed output files created.
     */

    BinaryStar(const unsigned long int p_Seed, const long int p_Id);

    // Copy constructor
    BinaryStar(const BinaryStar& p_Star) {

        m_ObjectId          = globalObjectId++;                                                 // get unique object id (don't copy source)
        m_ObjectPersistence = OBJECT_PERSISTENCE::PERMANENT;                                    // permanent - not an ephemeral clone

        m_BinaryStar     = new BaseBinaryStar(*(p_Star.m_BinaryStar));                          // copy underlying BaseBinaryStar
        m_SaveBinaryStar = new BaseBinaryStar(*(p_Star.m_SaveBinaryStar));                      // copy underlying Saved BaseBinaryStar
    }

    virtual ~BinaryStar() { delete m_BinaryStar; delete m_SaveBinaryStar; }


    // object identifiers - all classes have these
    OBJECT_ID           ObjectId() const            { return m_ObjectId; }
    OBJECT_TYPE         ObjectType() const          { return OBJECT_TYPE::BINARY_STAR; }
    OBJECT_PERSISTENCE  ObjectPersistence() const   { return m_ObjectPersistence; }
    STELLAR_TYPE        StellarType() const         { return m_StellarType; }


    // member functions
    long int            Id()                        { return m_BinaryStar->Id(); }
    EVOLUTION_STATUS    Evolve()                    { return m_BinaryStar->Evolve(); }
    bool                RevertState();
    void                SaveState();
    STELLAR_TYPE        Star1InitialType()          { return m_BinaryStar->InitialStellarType1(); }
    STELLAR_TYPE        Star1Type()                 { return m_BinaryStar->StellarType1(); }
    STELLAR_TYPE        Star2InitialType()          { return m_BinaryStar->InitialStellarType2(); }
    STELLAR_TYPE        Star2Type()                 { return m_BinaryStar->StellarType2(); }

    bool                PrintSwitchLog();

    // setters
    void                SetObjectId(const OBJECT_ID p_ObjectId)          { m_ObjectId = p_ObjectId; }
    void                SetPersistence(OBJECT_PERSISTENCE p_Persistence) { m_ObjectPersistence = p_Persistence; }


private:

    BinaryStar() { }

    OBJECT_ID          m_ObjectId;                                                              // Instantiated object's unique object id
    OBJECT_PERSISTENCE m_ObjectPersistence;                                                     // Instantiated object's persistence (permanent or ephemeral)
    STELLAR_TYPE       m_StellarType;                                                           // Stellar type defined in Hurley et al. 2000

    BaseBinaryStar    *m_BinaryStar;                                                            // Pointer to current binary star
    BaseBinaryStar    *m_SaveBinaryStar;                                                        // Pointer to saved binary star

};

#endif // __BinaryStar_h__
