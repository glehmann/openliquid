#include "Node.hpp"
#include "ParserContext.hpp"
#include "BaseFragment.hpp"

#ifndef __LIQUID_OUTPUTNODE
#define __LIQUID_OUTPUTNODE
namespace Liquid
{
    /// Filter for output node

    /// Manipulates an output by passing it through a 
    /// user defined filter function.
    class OutputFilter
    {
    public:
        /// Initialize a filter

        /// @param filterToken Token representing the filter
        OutputFilter(Token* filterToken);


        /// Dispose of a filter
        ~OutputFilter();


        /// Add an argument to the filter

        /// @param token Token representing the argument
        void AddArgument(Token* token)
        {
            this->_arguments.push_back(Fragment::Initialize(token));
        }


        /// Try to apply the filter
        
        /// @param input Input fragment
        /// @param output Output fragment
        /// @param context Rendering context
        bool TryApply(Fragment*& input,
                      Fragment*& output,
                      RenderContext& context);
    private:
        std::string _name;
        
        uint32_t _nameLineBegin;
        uint32_t _nameLineEnd;

        uint32_t _nameCharacterBegin;
        uint32_t _nameCharacterEnd;

        std::vector<Fragment*> _arguments;
    };



    /// Output node

    /// Represents output tags
    class OutputNode
        :   public Node
    {
    public:
        /// Initialize an output node
        OutputNode();


        /// Dispose of an output node
        virtual ~OutputNode();


        /// Try to parse to an output node
        
        /// @param context Parser context
        /// @returns true if parsing succeeded, otherwise false
        bool TryParse(ParserContext& context);
        
        
        /// Try to render the node
        
        /// @param context Rendering context
        /// @returns true if rendering succeeded, otherwise false
        virtual bool TryRender(RenderContext& context);
    private:
        Fragment* _baseFragment; ///< Fragment base
        std::vector<OutputFilter*> _filters; ///< Arguments
    };
}
#endif
