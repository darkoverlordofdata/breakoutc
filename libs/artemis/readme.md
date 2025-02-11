
public abstract class EntityObserver : Object 
        public abstract void Added(Entity e);
        public abstract void Changed(Entity e);
        public abstract void Deleted(Entity e);
        public abstract void Enabled(Entity e);
        public abstract void Disabled(Entity e);

public abstract class EntitySystem : EntityObserver 
        protected virtual void Begin() {}
        public virtual void End() {}
        protected virtual bool CheckProcessing() 
        public virtual void Initialize() {}
        public virtual void Inserted(Entity e) {}
        protected virtual void Removed(Entity e) {}
        
        protected abstract void ProcessEntities(ImmutableBag<Entity> entities);

public abstract class Manager : EntityObserver 
        public abstract void Initialize();

public abstract class DelayedEntityProcessingSystem : EntitySystem 
        protected abstract float GetRemainingDelay(Entity e);
        protected abstract void ProcessDelta(Entity e, float accumulatedDelta);
        protected abstract void ProcessExpired(Entity e);

public abstract class EntityProcessingSystem : EntitySystem 
        protected abstract void ProcessEach(Entity e);

public abstract class IntervalEntityProcessingSystem : IntervalEntitySystem 
		public abstract void ProcessEach(Entity e);

public abstract class IntervalEntitySystem : EntitySystem 


public abstract class VoidEntitySystem : EntitySystem 
        protected abstract void ProcessSystem();






