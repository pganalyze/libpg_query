-- From https://github.com/mattm/sql-style-guide
WITH hubspot_interest AS (
    SELECT
        email,
        timestamp_millis(property_beacon_interest) AS expressed_interest_at
    FROM hubspot.contact
    WHERE property_beacon_interest IS NOT NULL
), support_interest AS (
    SELECT conversation.email, conversation.created_at AS expressed_interest_at
    FROM
        helpscout.conversation
        JOIN helpscout.conversation_tag ON conversation.id = conversation_tag.conversation_id
    WHERE conversation_tag.tag = 'beacon-interest'
), combined_interest AS (
    SELECT *
    FROM hubspot_interest
    UNION ALL
    SELECT *
    FROM support_interest
), first_interest AS (
    SELECT email, min(expressed_interest_at) AS expressed_interest_at
    FROM combined_interest
    GROUP BY email
)
SELECT *
FROM first_interest
