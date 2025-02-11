#include "managers/teammanager.h"
#include "cfw.h"
#include "core/entity.h"
#include "core/manager-private.h"
#include "core/manager.h"
#include "core/world.h"
#include "ecs.h"
#include "managers/teammanager-private.h"

static bool ctor(void* self, va_list args) { return true; }
static bool equal(void* ptr1, void* ptr2) { return ptr1 == ptr2; }
static uint32_t hash(void* self) { return (uint32_t)self; }
static void* copy(void* self) { return NULL; }
static void dtor(void* self) {}

corefw(ECSTeamManager);

#define super ECSManager

method void* New(ECSTeamManager* this)
{
    static ECSIManager vtable = {
        .Initialize = (ECSManager_Initialize)Initialize,
        .Added = (ECSManager_Added)Added,
        .Changed = (ECSManager_Changed)Changed,
        .Deleted = (ECSManager_Deleted)Deleted,
        .Disabled = (ECSManager_Disabled)Disabled,
        .Enabled = (ECSManager_Enabled)Enabled,
    };

    New((super*) this, &vtable);

    this->PlayersByTeam = cfw_new(cfw_map, NULL);
    this->TeamByPlayer = cfw_new(cfw_map, NULL);
    return this;
}

method void Initialize(ECSTeamManager* this) 
{ 
    this->vptr->Initialize(this); 
}

method void SetWorld(ECSTeamManager* this, ECSWorld* world)
{
    SetWorld((super*)this, world);
}

method ECSWorld* GetWorld(ECSTeamManager* this)
{
    return GetWorld((super*)this);
}

method void Added(ECSTeamManager* this, ECSEntity* entity) 
{ 
    this->vptr->Added(this, entity); 
}

method void Changed(ECSTeamManager* this, ECSEntity* entity) 
{ 
    this->vptr->Changed(this, entity); 
}

method void Deleted(ECSTeamManager* this, ECSEntity* entity) 
{ 
    this->vptr->Deleted(this, entity); 
}

method void Disabled(ECSTeamManager* this, ECSEntity* entity) 
{ 
    this->vptr->Disabled(this, entity); 
}

method void Enabled(ECSTeamManager* this, ECSEntity* entity) 
{
    this->vptr->Enabled(this, entity); 
}

method char* GetTeam(ECSTeamManager* this, char* player)
{
    return Get(this->TeamByPlayer, player);
}

method void SetTeam(ECSTeamManager* this, char* player, char* team)
{
    RemoveFromTeam(this, player);

    Put(this->TeamByPlayer, player, team);

    CFArray* players = Get(this->PlayersByTeam, team);
    if (players == NULL) {
        players = cfw_new(cfw_array, NULL);
        Put(this->PlayersByTeam, team, players);
    }
    Add(players, player);
}

method CFArray* GetPlayers(ECSTeamManager* this, char* team)
{
    return Get(this->PlayersByTeam, team);
}

method void RemoveFromTeam(ECSTeamManager* this, char* player)
{
    char* team = Get(this->TeamByPlayer, player);
    if (Remove(this->TeamByPlayer, player)) {
        CFArray* players = Get(this->PlayersByTeam, team);
        if (players != NULL) {
            Remove(players, (void*)player);
        }
    }
}
