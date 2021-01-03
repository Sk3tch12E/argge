#include "Input.h"

namespace argge
{

    bool Input::getKey(int key)
    {

        for (int ki = 0; ki < keys.size(); ki++)
        {
             if (keys.at(ki) == key)
            {
                return true;
            }
        }

        return false;
    }

    //bool Input::getKeyDown(int key)
    //{
    //    for (size_t ki = 0; ki < downKeys.size(); ki++)
    //    {
    //        if (downKeys.at(ki) == key)
    //        {
    //            return true;
    //        }
    //    }

    //    return false;
    //}

    //bool Input::getKeyUp(int key)
    //{
    //    for (size_t ki = 0; ki < upKeys.size(); ki++)
    //    {
    //        if (upKeys.at(ki) == key)
    //        {
    //            return true;
    //        }
    //    }

    //    return false;
    //}

    //bool Input::clearKeysOnFrame()
    //{
    //    upKeys.clear();
    //    downKeys.clear();
    //    return false;
    //}

}