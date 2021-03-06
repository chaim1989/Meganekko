package org.meganekkovr.xml

import android.content.Context

import org.meganekkovr.Entity

/**
 * Define `opacity` attribute.
 */
internal class OpacityHandler : XmlAttributeParser.XmlAttributeHandler {

    override val attributeName = "opacity"

    override fun parse(entity: Entity, rawValue: String, context: Context) {

        val opacity = rawValue.toFloatOrNull() ?: return
        entity.opacity = opacity
    }
}
