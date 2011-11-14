#ifndef _IDENTIFY_H_
#define _IDENTIFY_H_

#include "cmd.h"
#include "identifyDefs.h"
#include "../Utils/fileSystem.h"


class Identify;    // forward definition
typedef boost::shared_ptr<Identify>             SharedIdentifyPtr;
#define CAST_TO_IDENTIFY(shared_trackable_ptr)  \
        boost::shared_polymorphic_downcast<Identify>(shared_trackable_ptr);


/**
* This class implements the Identify admin cmd
*
* @note This class may throw exceptions.
*/
class Identify : public Cmd
{
public:
    Identify(int fd);
    virtual ~Identify();

    /// Used to compare for NULL pointers being returned by allocations
    static SharedIdentifyPtr NullIdentifyPtr;

    /// The perfectly sized data buffer should be of this size
    static const uint16_t IDEAL_DATA_SIZE;

    /// @param ctrlr Pass true for controller, otherwise false for namespace
    void SetCNS(bool ctrlr);
    /// @return true for controller data, false for namespace data
    bool GetCNS();

    /**
     * Retrieve the specified PRP payload parameter. If the value can fit within
     * an uint64_t then it will be returned otherwise it will throw.
     * @param field Pass which struct field to return
     * @return The value if it fits, otherwise will throw if too large.
     */
    uint64_t GetValue(IdCtrlrCap field);
    uint64_t GetValue(IdNamespc field);

    /**
     * Send the entire contents of this cmds PRP payload to the named file.
     * @param filename Pass the filename as generated by macro
     *      FileSystem::PrepLogFile().
     * @param fileHdr Pass a custom file header description to dump
     */
    void Dump(LogFilename filename, string fileHdr);


private:
    Identify();

    bool mCtrlr;

    /// Details the fields within the identify controller capabilities struct
    static IdentifyDataType mIdCtrlrCapMetrics[];
    /// Details the fields within the identify namespace struct
    static IdentifyDataType mIdNamespcType[];


    /// General GetValue function to support the more specific public versions
    uint64_t GetValue(int field, IdentifyDataType *idData);
    void Dump(FILE *fp, int field, IdentifyDataType *idData);
};


#endif