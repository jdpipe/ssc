classdef Entry < handle
    %Entry object from SSC
    %   Object used to gather ssc module name, description and version
    %   information.
    
    properties (SetAccess = private)
        m_idx
        m_entry
    end
    properties
        Name
        Description
        Version
    end
    
    methods
        function obj = Entry()
            ssccall('load');
            obj.m_idx = 0;
        end
        function delete(obj)
            ssccall('unload');
        end
        function Reset(obj)
            obj.m_idx = 0;
        end
        function result = Get(obj)
            obj.m_entry = ssccall('module_entry', obj.m_idx);
            if (obj.m_entry == 0),
                obj.Reset;
                result = false;
            else
                obj.Name = ssccall('entry_name', obj.m_entry);
                obj.Description = ssccall('entry_description', obj.m_entry);
                obj.Version = ssccall('entry_version', obj.m_entry);
                obj.m_idx = obj.m_idx + 1;
                result = true;
            end
        end
    end
    
end

