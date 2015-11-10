/* Copyright 2015 Samsung Electronics Co., LTD
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.eje_c.meganekko.animation;

import com.eje_c.meganekko.HybridObject;
import com.eje_c.meganekko.SceneObject;
import com.eje_c.meganekko.Transform;

/** Size animation. */
@Deprecated
public class PositionAnimation extends TransformAnimation {

    private final float mStartX, mStartY, mStartZ;
    private final float mDeltaX, mDeltaY, mDeltaZ;

    /**
     * Position the transform, by potentially different amounts in each direction.
     * 
     * @param target
     *            {@link Transform} to animate.
     * @param duration
     *            The animation duration, in seconds.
     * @param positionX
     *            Target x position
     * @param positionY
     *            Target y position
     * @param positionZ
     *            Target z position
     */
    public PositionAnimation(Transform target, float duration, float positionX,
            float positionY, float positionZ) {
        super(target, duration);

        mStartX = mTransform.getPositionX();
        mStartY = mTransform.getPositionY();
        mStartZ = mTransform.getPositionZ();

        mDeltaX = positionX - mStartX;
        mDeltaY = positionY - mStartY;
        mDeltaZ = positionZ - mStartZ;
    }

    /**
     * Position the transform, by potentially different amounts in each direction.
     * 
     * @param target
     *            {@link SceneObject} containing a {@link Transform}
     * @param duration
     *            The animation duration, in seconds.
     * @param positionX
     *            Target x position
     * @param positionY
     *            Target y position
     * @param positionZ
     *            Target z position
     */
    public PositionAnimation(SceneObject target, float duration,
            float positionX, float positionY, float positionZ) {
        this(getTransform(target), duration, positionX, positionY, positionZ);
    }

    @Override
    protected void animate(HybridObject target, float ratio) {
        mTransform.setPosition(mStartX + ratio * mDeltaX, mStartY + ratio
                * mDeltaY, mStartZ + ratio * mDeltaZ);
    }
}
