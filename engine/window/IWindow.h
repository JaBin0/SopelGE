#pragma once


namespace Sopel {
/**! \brief Abstract inteface of the Sopel Engine window */
class IWindow {
public:
    virtual ~IWindow() {};
    
    /*! \brief Return whenever signal to close certain window was detected or not */
    virtual bool closeSignal() = 0;

    /*! \brief Initialize Window object. It's decoupled from constructor 
        to postpone whole process, so some settings can be adjusted. 
    */
   virtual void init() = 0;

    /*! \brief Update window state, pull events, swa 
    /*! \brief Update window state, pull events, swa 
    */
    virtual void update() = 0;
};
};